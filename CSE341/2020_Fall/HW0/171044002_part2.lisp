(defvar *file-to-be-read* "boundries.txt")
(defvar *file-to-be-write* "primedistribution.txt")

(defun primecrawler ()
    (let ((lowerBound) (upperBound))
        (multiple-value-bind (lb ub)
            (readFile *file-to-be-read*)
            (setq lowerBound lb)
            (setq upperBound ub))
        (writeFile *file-to-be-write* lowerBound upperBound)))

(defun readFile (fileName)
    (with-open-file (stream fileName :direction :input :if-does-not-exist nil)
        (when stream
            (values (read stream) (read stream)))))

(defun writeFile (fileName lb ub)
    (with-open-file (stream fileName :direction :output :if-exists :supersede :if-does-not-exist :create)
        (format stream "~a" (calcPrimeCrawler lb ub))))

(defun calcPrimeCrawler (lb ub)
    (when (<= lb ub) (concatenate 'string (printNumInfo lb) (calcPrimeCrawler (incf lb 1) ub))))

(defun printNumInfo (num)
    (cond
        ((isPrime num)
            (format nil "~a~a~%" num " is Prime"))
        ((isSemiPrime num)
            (format nil "~a~a~%" num " is Semi-prime"))))

(defun isPrime (num &optional (i 2))
    (cond
        ((<= num 1) nil)
        ((> i (/ num 2)) t)
        ((zerop (mod num i)) nil)
        (t (isPrime num (incf i 1)))))

(defun isSemiPrime (num &optional (i 2))
    (cond
        ((<= num 1) nil)
        ((> i( / num 2)) nil)
        ((and (zerop (mod num i)) (isPrime i) (isPrime (/ num i))) t)
        (t (isSemiPrime num (incf i 1)))))

(primecrawler)