(define car-word
  (lambda(str)
   (if (string-index str #\space)
    (substring str 0 (string-index str #\space))
    str)))

(define cdr-word
  (lambda(str)
   (if (string-index str #\space)
    (substring str (+ (string-index str #\space) 1)) 
    #f)))
     
(define try-cmd
 (lambda (commands str)
        (map (lambda (pair) 
               (if (> (string-length (car pair)) (string-length str)) 
                (if (string=? str (substring (car pair) 0 (string-length str))) 
                 (cdr pair)))) commands)))
                 


