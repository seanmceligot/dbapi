(define-module (my module))
(define my-so (dynamic-link "libguilegreendb.so"))
(dynamic-call "SWIG_init" my-so) ; make SWIG bindings

(define add-row
 (lambda (row index value-list)
  (if (not (null? value-list))
    (begin
     (format #t "adding ~A) ~A" index (car value-list))
     (newline)
     (Row-from-string-n row index (car value-list))
     (add-row row (+ index 1) (cdr value-list))))))

(begin 
    (let (
        (table_name (car (cdr (command-line))))
        (env (new-GreenEnv "."))
        (table '())
        (row '()))
    (GreenEnv-open env)
    (set! table (new-Table table_name env))
    (set! row (Table-new-row table))
    (add-row row 0 (cdr (cdr (command-line))))
    (Table-save table row)
    (Row-close row)
    (Table-close table)
    (GreenEnv-close env)))

