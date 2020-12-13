(defvar *file-to-be-read* "nested_list.txt")
(defvar *file-to-be-write* "flattened_list.txt")

(defun flattener ()
    (writeFile *file-to-be-write* (convertSingleList (readFile *file-to-be-read*))))

(defun readFile (fileName)
    (let ((myList) (stream (open fileName :if-does-not-exist nil)))
        (when stream
            (setq myList (createListFromFile stream))    
            (close stream)
            myList)))

(defun createListFromFile (stream)
    (let ((item (read stream nil)))
        (when item
            (concatenate 'list (list item) (createListFromFile stream)))))

(defun convertSingleList (myList)
    (cond
        ((and (listp myList) myList)
            (concatenate 'list (convertSingleList (car myList)) (convertSingleList (cdr myList))))
        (myList
            (list myList))))

(defun writeFile (fileName myList)
    (let ((stream (open fileName :direction :output)))
        (when stream
            (writeListToFile stream myList)
            (close stream))))

(defun writeListToFile (stream myList) ; Writes single list to file without parenthesis
    (when myList
        (format stream "~d " (car myList))
        (writeListToFile stream (cdr myList))))

(flattener)