
;(define foo (display 1))
;(define call (lambda (p) (p)))
;(define commands '(("load-table" . foo))) 
;(call (assoc-ref commands "load-table"))

;(define (test-app)
;  (let ((x 1 )
;    (y 2))
;  (define multiply
;   (lambda()
;    (display (* x y))
;    (newline)))
;  (multiply)))
;(test-app)

;(define load-table
; (lambda (table-name)
;  (display table-name)))
;
;(define (rep port)
;  (display "repl>")
;  ;(local-eval memoized-load-table ))
;  (write (local-eval (read port ) ))) 
;(call-with-input-string "(memozied-load-table)" rep )
;
;(define (memoize proc)
; (let ((cache '()))
;   (lambda args
;     (let ((hit (assoc args cache)))
;       (if hit (cdr hit)
;         (let ((result (apply proc args)))
;           (set! cache (cons (cons args result) cache))
;             result))))))
;(define memoized-load-table (memoize load-table))


