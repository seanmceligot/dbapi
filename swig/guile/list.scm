(define-module (my module))
(define my-so (dynamic-link "libguilegreendb.so"))
(dynamic-call "SWIG_init" my-so) ; make SWIG bindings

(define show-row
  (lambda (row colno)
  (if (< colno (Row-size row))
    (begin
       (format #t "~A) ~A" colno (Row-to-string-n row colno))
       (newline)
       (show-row row (+ 1 colno))))))

(define show-rows
  (lambda (table row pk)
    (if (not (null? row))
     (begin
      (show-row row 0)
      (show-rows table (Table-next table row pk) pk)
      (Row-close row)))))


(begin 
    (let (
        (table_name (car (cdr (command-line))))
        (env (new-GreenEnv "."))
        (table '())
        (schema '())
        (pk '()))
    (GreenEnv-open env)
    (set! table (new-Table table_name env))
    (set! schema (Table-get-schema table))
    (set! pk (Schema-get-name schema 0))
    (show-rows table (Table-first table pk) pk)
    (Table-close table)
    (GreenEnv-close env)))
