(defvar *is-open-quote* 0)

(defun gppinterpreter (&optional fileName)
	(let ((out (open "parsed_lisp.txt" :direction :output)))
		(if fileName (file-interpreter fileName out) (shell-interpreter out)) (close out)))

(defun shell-interpreter (out)
	(loop for line = (read-line) while (not (string= line "")) do (interpreter line out)))

(defun file-interpreter (fileName out)
	(let ((in (open fileName :if-does-not-exist nil)))
		(when in
			(loop for line = (read-line in nil) while line do
				(interpreter line out))
			(close in))
		(unless in
			(format t "Error! No such file: '~a'~%" fileName))))

(defun interpreter (str out)
	(let ((lst (str-to-list str)))
		(map nil #'(lambda (token) (write-line (tokenize token (get-tokens)) out)) lst)))

(defun get-tokens ()
	(concatenate 'list (get-keywords) (get-operators)))

(defun get-keywords ()
	(pairlis '("false" "true" "disp"  "load" "exit" "if" "for" "deffun" "set" "concat" "append" "list" "nil" "less" "equal" "not" "or" "and")
		'("KW_FALSE" "KW_TRUE" "KW_DISP" "KW_LOAD" "KW_EXIT" "KW_IF" "KW_FOR" "KW_DEFFUN" "KW_SET" "KW_CONCAT" "KW_APPEND" "KW_LIST" "KW_NIL" "KW_LESS" "KW_EQUAL" "KW_NOT" "KW_OR" "KW_AND")))

(defun get-operators ()
	(pairlis '("," "\"" "\"" "**" ")" "(" "*" "/" "-" "+")
		'("OP_COMMA" "OP_CC" "OP_OC" "OP_DBLMULT" "OP_CP" "OP_OP" "OP_MULT" "OP_DIV" "OP_MINUS" "OP_PLUS")))

(defun tokenize (token tokenList)
	(let ((value))
		(if (or
			(setf value (tokenize-key-op token tokenList))
			(setf value (tokenize-identifier token tokenList))
			(setf value (tokenize-value token))
			(setf value (tokenize-comment token)))
		value (format nil "SYNTAX ERROR ~a cannot be tokenized" token))))

(defun tokenize-key-op (token keys)
	(let ((var (assoc token keys :test #'string=)))
		(if (string= (car var) "\"")
			(if (zerop *is-open-quote*) (progn (setf *is-open-quote* 1) "OP_OC") (progn (setf *is-open-quote* 0) "OP_CC"))
			(cdr var))))

(defun tokenize-identifier (token key) ; [[:alpha:]][[:alnum:]]*
	(if (is-alpha (char token 0))
		(loop for i across token do (when (not (is-alnum i)) (return-from tokenize-identifier)))
		(return-from tokenize-identifier)) "IDENTIFIER")

(defun tokenize-value (token) ; ("+"?|"-"?)([[:digit:]]|[1-9][[:digit:]]+)
	(when (and (char= (char token 0) #\0) (not (= (length token) 1))) (return-from tokenize-value))

	(loop for i across token do (when (not (is-digit i)) (return-from tokenize-value)))
	"VALUE")

(defun tokenize-comment (token) ; ";;".*
	(when (and (> (length token) 1) (is-semicolon (char token 0)) (is-semicolon (char token 1))) "COMMENT"))

(defun str-to-list (str)
	(when (is-not-zero str)
		(let ((founded (fpos-delim str)) (fchr) (pos) (posQuote))
			(unless (null founded) (setf fchr (car founded)) (setf pos (cdr founded)))

			(cond 
				((null founded) (list str))
				((is-bracket fchr)
					(if (zerop pos)
						(cons (subseq str 0 1) (str-to-list (subseq str 1)))
						(cons (subseq str 0 pos) (cons (subseq str pos (+ pos 1)) (str-to-list (subseq str (+ pos 1)))))))
				((is-space fchr)
					(if (zerop pos)
						(str-to-list (subseq str 1))
						(cons (subseq str 0 pos) (str-to-list (subseq str (+ pos 1))))))
				((is-quote fchr)
					(if (zerop pos)
						(cons (subseq str 0 1) (str-to-list (subseq str 1)))
						(cons (subseq str 0 pos) (cons (subseq str pos (+ pos 1)) (str-to-list (subseq str (+ pos 1)))))))
				(t (if (or (<= (length str) (+ pos 1)) (not (is-semicolon (char str (+ pos 1)))))
						(if (zerop pos)
							(cons (subseq str 0 1) (str-to-list (subseq str 1)))
							(cons (subseq str 0 pos) (cons (subseq str pos (+ pos 1)) (str-to-list (subseq str (+ pos 1))))))
						(if (zerop pos) (list str) (list (subseq str 0 pos) (subseq str pos)))))))))

(defun fpos-delim (str &optional (pos 0))
	(when (is-not-zero str)
		(if (or (is-bracket (char str 0)) (is-space (char str 0)) (is-semicolon (char str 0)) (is-quote (char str 0)))
			(cons (char str 0) pos)
			(fpos-delim (subseq str 1) (+ pos 1)))))

(defun fpos-quote (str &optional (pos 0))
	(when (is-not-zero str) (if (is-quote (char str 0)) pos (fpos-quote (subseq str 1) (+ pos 1)))))

(defun is-alnum (chr)
	(or (and (char>= chr #\0) (char<= chr #\9)) (and (char>= chr #\A) (char<= chr #\Z)) (and (char>= chr #\a) (char<= chr #\z))))

(defun is-alpha (chr)
	(or (and (char>= chr #\A) (char<= chr #\Z)) (and (char>= chr #\a) (char<= chr #\z))))

(defun is-digit (chr)
	(and (char>= chr #\0) (char<= chr #\9)))

(defun is-space (chr)
	(or (and (char>= chr (code-char 9)) (char<= chr (code-char 13))) (char= chr (code-char 32))))

(defun is-bracket (chr)
	(or (char= chr #\() (char= chr #\))))

(defun is-quote (chr)
	(char= chr #\"))

(defun is-semicolon (chr)
	(char= chr #\;))

(defun is-not-zero (str)
	(not (zerop (length str))))

(if *args* (gppinterpreter (car *args*)) (gppinterpreter))