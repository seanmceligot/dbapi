
(define show-pair-pre
 (lambda (pre pair) 
  (display pre)
  (display pair)
  (newline)))

(define show-pair
 (lambda (pair) 
  (display "pair: ")
  (display pair)
  (newline)))


(define for-each-pair 
 (lambda (fn args)
     (if (pair? args)
      (begin
          (fn (list-head args 2))
          (for-each-pair fn (list-tail args 2))))))

(display "start")
(newline)
(define my-show-pair 
 (lambda (pair)
  (show-pair-pre ">>>> " pair)))
(for-each-pair my-show-pair (cdr (command-line)))

(begin
(for-each-pair (lambda (my-pair) 
                  (show-pair-pre "! " my-pair))
                (cdr (command-line))))
