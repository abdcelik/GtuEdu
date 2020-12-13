(defvar *file-to-be-read* "paragraph.txt")
(defvar *file-to-be-write* "huffman_codes.txt")

(defstruct Node
    data
    freq
    left
    right
)

(defstruct HuffmanCode
    character
    code
)

(defun Huffman-Code ()
    (let ((myList))
        (setq myList (createHuffmanTree (readFile *file-to-be-read*)))
        (writeFile *file-to-be-write* (buildWritingList (car myList)))))

(defun newNode (chr freq &optional left right)
    (make-Node :data chr :freq freq :left left :right right))

(defun newHuffManCode (character code)
    (make-HuffmanCode :character character :code code))

(defun readFile (fileName)
    (let ((myList) (stream (open fileName :if-does-not-exist nil)))
        (when stream
            (loop for chr = (read-char stream nil) while chr do
                (when (< (char-code chr) 256)
                    (setq myList (fixupList myList chr))))
            (close stream)
            myList)))

(defun fixupList (myList chr)
    (when (zerop (length myList)) (return-from fixupList (list (newNode chr 1))))

    (let ((temp myList))
        (loop while (not (zerop (length temp))) do
            (cond
                ((equal chr (Node-data (car temp))) (setf (Node-freq (car temp)) (+ (Node-freq (car temp)) 1)) (return-from fixupList myList))
                (t (setq temp (cdr temp))))))

    (append myList (list (newNode chr 1))))

(defun extractMin (myList)
    (let ((temp))
        (setq temp (findMinItem myList))
        (values (removeItem myList temp) temp)))

(defun findMinItem (myList)
    (when (zerop (length myList)) (return-from findMinItem))
    
    (let ((i 0) (minIndex 0) (minItem (car myList)))
        (setq myList (cdr myList))
        (loop while (not (zerop (length myList))) do
            (setq i (+ i 1))
            (when (> (Node-freq minItem) (Node-freq (car myList)))
                (setq minIndex i)
                (setq minItem (car myList)))
            (setq myList (cdr myList)))
        minItem))

(defun removeItem (myList item)
    (let ((newList nil))
        (cond
            ((and (not (zerop (length myList))) (not (eq item (car myList))))
                (setq newList (append newList (list(car myList))))
                (setq newList (append newList (removeItem (cdr myList) item))))
            ((and (not (zerop (length myList)))  (eq item (car myList)))
                (removeItem (cdr myList) item))
            (t nil))))

(defun createHuffmanTree (myList)
    (loop while (not (= (length myList) 1)) do
        (let ((item1) (item2))
            (multiple-value-bind (newList minItem)
                (extractMin myList)
                (setq myList newList)
                (setq item1 minItem))
            (multiple-value-bind (newList minItem)
                (extractMin myList)
                (setq myList newList)
                (setq item2 minItem))
            (push (newNode nil (+ (Node-freq item1) (Node-freq item2)) item1 item2) myList)))
    myList)

(defun isLeaf (node)
    (and (null (Node-left node)) (null (Node-right node))))

(defun buildWritingList (node &optional path)
    (when (null node) (return-from buildWritingList nil))

    (let ((codes))
        (if (null (isLeaf node))
            (progn
                (setq codes (merge 'list codes (buildWritingList (Node-left node) (concatenate 'string path "0")) #'state))
                (setq codes (merge 'list codes (buildWritingList (Node-right node) (concatenate 'string path "1")) #'state)))
            (list (newHuffManCode (Node-data node) path)))))

(defun state (val1 val2)
    (let ((diff (- (length (HuffmanCode-code val1)) (length (HuffmanCode-code val2)))))
        (cond
            ((< diff 0) t)
            ((> diff 0) nil)
            ((zerop diff) (string> (HuffmanCode-character val1) (HuffmanCode-character val2))))))

(defun writeFile (fileName myList)
    (let ((stream (open fileName :direction :output)))
        (when stream
            (writeFileHelper stream myList)
            (close stream))))

(defun writeFileHelper (stream myList)
    (when (not (zerop (length myList)))
        (writeOneCode stream (car myList))
        (writeFileHelper stream (cdr myList))))

(defun writeOneCode (stream huffmanCode)
    (write-char (HuffmanCode-character huffmanCode) stream)
    (format stream ": ")
    (write-line (HuffmanCode-code huffmanCode) stream))

(Huffman-Code)