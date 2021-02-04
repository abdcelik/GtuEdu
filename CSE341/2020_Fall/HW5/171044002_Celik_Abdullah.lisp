(defun read-file (fileName)
	(let ((myList) (stream (open fileName :if-does-not-exist nil)))
		(when stream
			(setq myList (create-list-from-file stream))    
			(close stream)
			myList)))

(defun write-file (fileName myList)
	(let ((stream (open fileName :direction :output)))
		(when stream
			(write-line-by-line stream myList)
			(close stream))))

(defun write-line-by-line (out lst)
	(when lst
		(format out "~s~%" (car lst))
		(write-line-by-line out (cdr lst))))

(defun create-list-from-file (stream)
	(let ((item (read stream nil)))
		(when item
			(concatenate 'list (list item) (create-list-from-file stream)))))

(defun prolog (lst)
	(let ((query) (fact) (prec) (res))
		(loop for i while (< i (length lst)) do
			(if (null (car (nth i lst)))
				(setq query (concatenate 'list query (cdr (nth i lst))))
				(if (null (cadr (nth i lst)))
					(setq fact (concatenate 'list fact (list (car (nth i lst)))))
					(setq prec (concatenate 'list prec (list (nth i lst)))))))
		(answer-queries query fact prec)))

(defun answer-queries (query fact prec)
	(when query
		(cons (answer-query (car query) fact prec) (answer-queries (cdr query) fact prec))))

(defun answer-query (query fact prec)
	(let ((res))
		(cond
			((is-fact query fact) (answer-fact query fact))
			((is-predicate query prec) (answer-predicate query nil fact prec))
			(t nil))))

(defun answer-fact (query fact)
	(if (has-variable (cadr query)) (find-var query fact) t))

(defun answer-predicate (head body fact prec)
	(when (null head) (return-from answer-predicate t))

	(when (is-fact head fact)
		(if (listp (answer-fact head fact))
			(return-from answer-predicate (apply-keys body (find-var head fact) fact prec))
			(return-from answer-predicate (answer-predicate (car body) (cdr body) fact prec))))

	(let ((precs (is-predicate head prec)) (deneme))
		(when precs
			(if (has-variable (cadr head))
				(return-from answer-predicate (answer-predicate-helper head precs fact prec))
				(when (answer-predicate (caadar precs) (cdadar precs) fact prec) (return-from answer-predicate t)))))
	nil)

(defun answer-predicate-helper (head precs fact prec)
	(when precs
		(if (has-variable (caar precs))
			(progn
				(print "Query has variable and precdicate's head has variable. Program can't query!")
				nil
			)
			(let ((keys (find-var head (list (caar precs)))) (body))
				(setq body (unification (cdar precs) (car keys)))
				(if (answer-predicate (caar body) (cdar body) fact prec)
					(cons (car keys) (answer-predicate-helper head (cdr precs) fact prec))
					(answer-predicate-helper head (cdr precs) fact prec))))))

(defun apply-keys (body keys fact prec)
	(when keys
		(let ((new-body (unification body (car keys))))
			(if (answer-predicate (car new-body) (cdr new-body) fact prec)
				(cons (car keys) (apply-keys body (cdr keys) fact prec))
				(apply-keys body (cdr keys) fact prec)))))

(defun unification (lst keys)
	(when lst
		(if (listp (car lst))
			(concatenate 'list (list (unification (car lst) keys)) (unification (cdr lst) keys))
			(progn
				(loop for i while (< i (length keys)) do
					(when (is-equal (car lst) (car (nth i keys)))
						(return-from unification (cons (cdr (nth i keys)) (unification (cdr lst) keys)))))
				(cons (car lst) (unification (cdr lst) keys))))))

(defun find-var (query rule) 
	(when rule
		(if (check-query query (car rule))
			(cons (find-var-helper (cadr query) (cadar rule)) (find-var query (cdr rule)))
			(find-var query (cdr rule)))))

(defun find-var-helper (lst1 lst2)
	(when lst1
		(if (is-variable (car lst1))
			(cons (cons (car lst1) (car lst2)) (find-var-helper (cdr lst1) (cdr lst2)))
			(find-var-helper (cdr lst1) (cdr lst2)))))

(defun is-fact (query fact)
	(when fact
		(if (check-query query (car fact)) t (is-fact query (cdr fact)))))

(defun is-predicate (query prec)
	(when prec
		(if (check-query query (caar prec))
			(cons (car prec) (is-predicate query (cdr prec)))
			(is-predicate query (cdr prec)))))

(defun check-query (query rule)
	(when (and (string= (car query) (car rule)) (= (length (cadr query)) (length (cadr rule))))
		(loop for i while (< i (length (cadr query))) do
			(unless (or (is-variable (nth i (cadr query))) (is-variable (nth i (cadr rule))) (is-equal (nth i (cadr query)) (nth i (cadr rule))))
				(return-from check-query nil))) t))

(defun has-variable (query)
	(when query (if (is-variable (car query)) t (has-variable (cdr query)))))

(defun is-variable (str)
	(when (and (stringp str) (> (char-code (char str 0)) 64) (< (char-code (char str 0)) 91)) t))

(defun is-equal (o1 o2)
	(if (and (stringp o1) (stringp o2))
		(string= o1 o2)
		(when (and (not (stringp o1)) (not (stringp o2))) (= o1 o2))))

(write-file "output.txt" (prolog (car (read-file "input.txt"))))