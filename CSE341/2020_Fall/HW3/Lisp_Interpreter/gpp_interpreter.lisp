(load "gpp_lexer.lisp")
(defvar *output-file-name* "output.txt")
(defvar table nil)

(defun gppinterpreter (&optional file-name)
	(let ((out (open *output-file-name* :direction :output)))
		(if file-name (file-interpreter file-name out) (shell-interpreter out)) (close out)))

(defun shell-interpreter (out)
	(loop for line = (read-line) while (not (string= line "")) do (START (lexer line) out)))

(defun file-interpreter (file-name out)
	(let ((in (open file-name :if-does-not-exist nil)))
		(when in
			(loop for line = (read-line in nil) while line do (START (lexer line) out))
			(close in))
		(unless in (format out "Error! No such file: ~a~%" file-name))))

(defun START (tokens out &optional res (index 0))
	(when (zerop (length tokens)) (return-from START nil))
	(if (setq res (INPUT tokens index))
		(progn
			(format out "Syntax OK.~%Result: ~s~%" (car res))
			(unless (equal (length tokens) (cdr res)) (START tokens out :input (cdr res))))
		(format out "SYNTAX_ERROR Expression not recognized~%")))

; Returns (result . index) or nil
(defun INPUT (seq i)
	(let ((res))
		(cond
			((setq res (EXPI seq i)) res)
			((setq res (EXPB seq i)) res)
			((setq res (EXPLISTI seq i)) res)
			)))

; Returns (result . index) or nil
(defun EXPI (seq i)
	(let ((res))
		(cond
			((setq res (EXPI-rule1 seq i)) res) ; EXPI-> (+ EXPI EXPI) | (- EXPI EXPI) | (* EXPI EXPI) | (/ EXPI EXPI)
			((setq res (EXPI-rule2 seq i)) res) ; EXPI-> VALUE
			((setq res (EXPI-rule3 seq i)) res) ; EXPI-> IDENTIFIER
			((setq res (EXPI-rule4 seq i)) res) ; EXPI-> (set ID EXPI)
			((setq res (EXPI-rule5 seq i)) res)))) ; EXPI-> (if EXPB EXPI) | (if EXPB EXPI EXPI)

(defun EXPI-rule1 (seq i) ; EXPI-> (+ EXPI EXPI) | (- EXPI EXPI) | (* EXPI EXPI) | (/ EXPI EXPI)
	(let ((lo) (ro) (op))
		(when (and (string= "OP_OP" (car (nth i seq))) (is-EXPI-operator (cdr (nth (setq op (+ i 1)) seq))) (setq lo (EXPI seq (+ i 2))))
			(when (and (setq ro (EXPI seq (cdr lo))) (string= "OP_CP" (car (nth (cdr ro) seq))))
				(return-from EXPI-rule1 (cons (perform-op (car lo) (car ro) (cdr (nth op seq))) (+ 1 (cdr ro))))))))

(defun EXPI-rule2 (seq i) ; EXPI-> VALUE
	(when (string= "VALUE" (car (nth i seq))) (return-from EXPI-rule2 (cons (parse-integer (cdr (nth i seq))) (+ i 1)))))

(defun EXPI-rule3 (seq i) ; EXPI-> IDENTIFIER
	(when (string= "IDENTIFIER" (car (nth i seq)))
		(cons (tableGet (cdr (nth i seq))) (+ i 1))))

(defun EXPI-rule4 (seq i) ; EXPI-> (set ID EXPI)
	(let ((val) (id (cdr (nth (+ i 2) seq))))
		(when (and (string= "OP_OP" (car (nth i seq))) (string= "KW_SET" (car (nth (+ i 1) seq))) (string= "IDENTIFIER" (car (nth (+ i 2) seq))))
			(when (and (setq val (EXPI seq (+ i 3))) (string= "OP_CP" (car (nth (cdr val) seq)))) 
				(tableAdd id (car val))
				(cons (car val) (+ (cdr val) 1))))))

(defun EXPI-rule5 (seq i) ; EXPI-> (if EXPB EXPI) | (if EXPB EXPI EXPI)
	(let ((condition) (lo) (ro))
		(when (and (string= "OP_OP" (car (nth i seq))) (string= "KW_IF" (car (nth (+ i 1) seq))) (setq condition (EXPB seq (+ i 2))))
			(when (setq lo (EXPI seq (cdr condition)))
				(if (string= "OP_CP" (car (nth (cdr lo) seq)))
					(if (= (car condition) 1) (cons (car lo) (+ (cdr lo) 1)) (cons 0 (+ (cdr lo) 1)))
					(when (and (setq ro (EXPI seq (cdr lo))) (string= "OP_CP" (car (nth (cdr ro) seq))))
						(if (= (car condition) 1) (cons (car lo) (+ (cdr ro) 1)) (cons (car ro) (+ (cdr ro) 1)))))))))

(defun EXPB (seq i)
	(let ((res))
		(cond
			((setq res (EXPB-rule1 seq i)) res) ; EXPB-> (and EXPB EXPB) | (or EXPB EXPB) | (equal EXPB EXPB) | (equal EXPI EXPI)
			((setq res (EXPB-rule2 seq i)) res) ; EXPB-> (not EXPB)
			((setq res (EXPB-rule3 seq i)) res)))) ; EXPB-> BinaryValue

(defun EXPB-rule1 (seq i) ; EXPB-> (and EXPB EXPB) | (or EXPB EXPB) | (equal EXPB EXPB) | (equal EXPI EXPI)
	(let ((lo) (ro) (op (+ i 1)) (res) (cp-flag))
		(unless (string= "OP_OP" (car (nth i seq))) (return-from EXPB-rule1 nil))
		(when (or (string= "KW_AND" (car (nth (+ i 1) seq))) (string= "KW_OR" (car (nth (+ i 1) seq)))) 
			(when (setq lo (EXPB seq (+ i 2))) (setq ro (EXPB seq (cdr lo)))
				(setq res (cons (perform-op (car lo) (car ro) (cdr (nth op seq))) (+ 1 (cdr ro))))
				(setq cp-flag t)))
		(when (string= "KW_EQUAL" (car (nth (+ i 1) seq)))
			(if (setq lo (EXPB seq (+ i 2)))
				(when (setq ro (EXPB seq (cdr lo))) (setq res (cons (perform-op (car lo) (car ro) (cdr (nth op seq))) (+ (cdr ro) 1))) (setq cp-flag t))
				(when (and (setq lo (EXPI seq (+ i 2))) (setq ro (EXPI seq (cdr lo)))) (setq res (cons (perform-op (car lo) (car ro) (cdr (nth op seq))) (+ (cdr ro) 1))) (setq cp-flag t))))
		(when (and cp-flag (string= "OP_CP" (car (nth (cdr ro) seq)))) res)))

(defun EXPB-rule2 (seq i) ; EXPB-> (not EXPB)
	(let ((operand))
		(when (and (string= "OP_OP" (car (nth i seq))) (string= "KW_NOT" (car (nth (+ i 1) seq))))
			(when (and (setq operand (EXPB seq (+ i 2))) (string= "OP_CP" (car (nth (cdr operand) seq))))
				(cons (if (= (car operand) 0) 1 0) (+ (cdr operand) 1))))))

(defun EXPB-rule3 (seq i) ; EXPB-> BinaryValue
	(cond
		((string= "KW_TRUE" (car (nth i seq))) (cons 1 (+ i 1)))
		((string= "KW_FALSE" (car (nth i seq))) (cons 0 (+ i 1)))))

(defun EXPLISTI (seq i)
	(let ((res))
		(cond
			((setq res (EXPLISTI-rule1 seq i)) res) ; EXPLISTI -> (concat EXPLISTI EXPLISTI)
			((setq res (EXPLISTI-rule2 seq i)) res) ; EXPLISTI -> (append EXPI EXPLISTI)
			((setq res (EXPLISTI-rule3 seq i)) res)))) ; EXPLISTI -> LISTVALUE

(defun EXPLISTI-rule1 (seq i) ; EXPLISTI -> (concat EXPLISTI EXPLISTI)
	(unless (and (string= "OP_OP" (car (nth i seq))) (string= "KW_CONCAT" (car (nth (+ i 1) seq)))) (return-from EXPLISTI-rule1))
	(let ((lo) (ro))
		(unless (and (setq lo (EXPLISTI seq (+ i 2))) (setq ro (EXPLISTI seq (cdr lo))) (string= "OP_CP" (car (nth (cdr ro) seq)))) (return-from EXPLISTI-rule1))
		(cons (concatenate 'list (car lo) (car ro)) (+ (cdr ro) 1))))

(defun EXPLISTI-rule2 (seq i) ; EXPLISTI -> (append EXPI EXPLISTI)
	(unless (and (string= "OP_OP" (car (nth i seq))) (string= "KW_APPEND" (car (nth (+ i 1) seq)))) (return-from EXPLISTI-rule2))
	(let ((lo) (ro))
		(unless (and (setq lo (EXPI seq (+ i 2))) (setq ro (EXPLISTI seq (cdr lo))) (string= "OP_CP" (car (nth (cdr ro) seq)))) (return-from EXPLISTI-rule2))
		(cons (concatenate 'list (list (car lo)) (car ro)) (+ (cdr ro) 1))))

(defun EXPLISTI-rule3 (seq i) ; EXPLISTI -> LISTVALUE; LISTVALUE -> (VALUES) | () | null
	(when (string= "KW_NIL" (car (nth i seq))) (return-from EXPLISTI-rule3 (cons nil (+ i 1))))
	(unless (string= "OP_OP" (car (nth i seq))) (return-from EXPLISTI-rule3))
	(when (string= "OP_CP" (car (nth (+ i 1) seq))) (return-from EXPLISTI-rule3 (cons '() (+ i 2))))

	(let ((op))
		(setq op (rule-VALUES seq (+ i 1)))
		(when (string= "OP_CP" (car (nth (cdr op) seq))) (cons (car op) (+ (cdr op) 1)))))

(defun rule-VALUES (seq i) ; VALUES-> VALUES IntegerValue | IntegerValue
	(let ((op))
		(when (not (string= "VALUE" (car (nth i seq))))
			(return-from rule-VALUES (cons nil i)))
		(cons (cons (parse-integer (cdr (nth i seq))) (car (setq op (rule-VALUES seq (+ i 1))))) (cdr op))))

(defun tableAdd (id val)
	(if (tableGet id) (tableUpdate table id val) (push (cons id val) table)))

(defun tableUpdate (table id val)
	(when table (if (string= (caar table) id) (setf (cdar table) val) (tableUpdate (cdr table) id val))))

(defun tableGet (id)
	(tableGet-Helper table id))

(defun tableGet-Helper (table id)
	(when table (if (string= (caar table) id) (cdar table) (tableGet-Helper (cdr table) id))))

(defun is-EXPI-operator (op)
	(let ((operators '("+" "-" "*" "/"))) 
		(loop for i in operators do (when (string= i op) (return-from is-EXPI-operator t)))))

(defun perform-op (n1 n2 op)
	(cond
		((string= op "+") (+ n1 n2))
		((string= op "-") (- n1 n2))
		((string= op "*") (* n1 n2))
		((string= op "/") (/ n1 n2))
		((string= op "and") (logand n1 n2))
		((string= op "or") (logior n1 n2))
		((string= op "equal") (= n1 n2))))

(if *args* (gppinterpreter (car *args*)) (gppinterpreter))