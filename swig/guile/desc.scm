(define-module (my module))
(define my-so (dynamic-link "libguilegreendb.so"))
(dynamic-call "SWIG_init" my-so) ; make SWIG bindings

(define desc 
 (lambda (schema size i)
	(if (< i size)
	 (begin 
		(display i)
		(display ") ")
		(display (Schema-get-name schema i))
		(newline)
		(set! i (+ 1 i))
		(desc schema size i)))))

(begin 
    (let (
        (table_name (car (cdr (command-line))))
        (env (new-GreenEnv "."))
        (table '())
        (schema '()))
    (GreenEnv-open env)
    (set! table (new-Table table_name env))
    (set! schema (Table-get-schema table))
    (desc schema (Schema-size schema) 0)
    (Table-close table)
    (GreenEnv-close env)))

