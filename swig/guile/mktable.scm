(define-module (my module))
(define my-so (dynamic-link "libguilegreendb.so"))
(dynamic-call "SWIG_init" my-so)

(define mkcol
 (lambda (schema tnpair)
  (let ( 
   (type (car tnpair))
   (name (car (cdr tnpair))))
    (format #t "add-column name: ~A type: ~A" name type)
    (newline)
    (Schema-add-column schema name (string->number type) 0))))

(define for-each-pair 
 (lambda (fn pair-list)
     (if (pair? pair-list)
      (begin
        (fn (list-head pair-list 2))
        (for-each-pair fn (list-tail pair-list 2))))))

(define (bound-mkcol schema)
 (lambda (p)
  (mkcol schema p)))
    
 (begin 
    (let (
        (table_name (car (cdr (command-line))))
        (env (new-GreenEnv "."))
        (table '())
        (schema '()))
    (GreenEnv-open env)
    (set! table (new-Table table_name env))
    (set! schema (Table-get-schema table))
    (if (> (Schema-size schema) 0)
     (begin
      (display "Table already created ")
      (newline)
      (quit)) )
     (format #t "mktable: ~A" (Table-get-name table))
     (newline)
     (let (
           (fn (bound-mkcol schema))) 
      (for-each-pair fn (cdr (cdr (command-line)))))
     (Table-close table)
     (GreenEnv-close env)))


