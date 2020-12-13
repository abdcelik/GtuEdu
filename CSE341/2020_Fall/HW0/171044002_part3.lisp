(defvar *file-to-be-read* "integer_inputs.txt")
(defvar *file-to-be-write* "collatz_outputs.txt")

(defun collatzSequence ()
    (writeFile *file-to-be-write* (readFile *file-to-be-read*)))

(defun readFile (fileName)
    (let 
        ((i 0) (numbers) (stream (open fileName :if-does-not-exist nil)))
        
        (when stream
            (loop for line = (read stream nil) while (and line (< i 5)) do
                (setq numbers (append numbers (list line)))
                (setq i (+ i 1)))
            (close stream))
        numbers))

(defun writeFile (fileName nums)
    (let
        ((stream (open fileName :direction :output)))

        (when stream
            (format stream "~a" (writeFileHelper nums))
            (close stream))))

(defun writeFileHelper (nums) ; Removes element from list of number and creates a string version recursively
    (cond
        ((zerop (length nums)) nil)
        (t (concatenate 'string (startCollatzSequence (car nums)) (writeFileHelper (cdr nums))))))

(defun startCollatzSequence (num) ; Returns string forms of sequence
    (if (< num 1)
        (format nil "~d: Number must be greater than 1!~%" num)
        (format nil "~d: ~a~%" num (computeCollatzSequence num))))

(defun computeCollatzSequence (num) ; Computes collatz sequence as recursion and returns string version of sequence
    (cond
        ((<= num 1) "1")
        ((evenp num) (format nil "~d ~a" num (computeCollatzSequence (/ num 2))))
        (t (format nil "~d ~a" num (computeCollatzSequence (+ (* num 3) 1))))))

(collatzSequence)