	
(define-module (my module))
(define my-so (dynamic-link "libguilegreendb.so"))
(dynamic-call "SWIG_init" my-so) ; make SWIG bindings

(use-modules (gtk gtk))
(use-modules (ice-9 debug))

(load "completion.scm") 
(load "browse.scm") 

(define cleanup-table
 (lambda(table)
  (if (not (null? table)) 
   (begin 
    (Table-close table)
    (set! table #f)))))

(define cleanup-row
 (lambda(row)
  (if (not (null? row)) 
   (begin 
    (Row-close row)
    (set! row #f)))))
 
(define (greendb-app)
  (let (
    (window (gtk-window-new 'toplevel))
    (vbox (gtk-vbox-new #f 0))
    (frame (gtk-frame-new ""))
    (cmd-entry (gtk-entry-new))
    (status-bar (gtk-statusbar-new))
    (test 99)
    (x 10)
    (current-grid #f)
    (row-vector #f)
    (current-row #f)
    (env #f)
    (current-table #f)
    (current-schema #f)
    (current-index-name #f)
    (commands '(("load-table" . 1) ("add-row" . 2) ("create-table" . 3) ("add-column"))))
  (define (cmd-entry-insert-text . opt-dup)
   (display opt-dup)
   (newline)
   (display (car opt-dup))
   (newline)
   ;(display (list-ref opt-dup 1))
   (display (cdr opt-dup)))

  (define (add-row str-items row col-no)
     (if str-items 
       (begin 
        (backtrace)
         (display "add: ")(display col-no)(display (car-word str-items))(newline)(force-output)
         (Row-from-string-n row col-no (car-word str-items))
         (display "added: ")(display (Row-to-string-n row col-no))(newline)(force-output)
         (add-row (cdr-word str-items) row (+ col-no 1)))
        (begin
         (display "save row")
         (Table-save current-table row)
         (cleanup-row row))))
  (define (load-table table-name)
      (cleanup-row current-row)
      (cleanup-table current-table)
      (set! current-table (new-Table table-name env))
      (set! current-schema (Table-get-schema current-table))
      (if current-grid
        (begin
         (cleanup-table current-table)
         (gtk-container-remove frame current-grid)))
      (set! current-grid (gtk-clist-new (Schema-size current-schema)))
      (browser-set-clist-titles current-grid current-schema (Schema-size current-schema) 0)
      (gtk-clist-column-titles-show current-grid)
      (gtk-container-add frame current-grid)
      (set! current-index-name (Schema-get-name current-schema 0))
      (set! current-row (Table-first current-table current-index-name))
      (browser-show-rows current-grid current-table current-row current-index-name)
      (gtk-widget-show current-grid)
      (Table-close current-table))
 
  (gtk-widget-show vbox)
  (gtk-container-add window vbox)
  (gtk-widget-show frame)
  (gtk-box-pack-start vbox frame #t #t 0)
  (for-each (lambda (w)
  	(gtk-widget-show w)
  	(gtk-box-pack-start vbox w #f #f 0)) 
   (list cmd-entry status-bar))
    
  (gtk-widget-show status-bar)
  (gtk-box-pack-start vbox status-bar #f #f 0)
  (set! env (new-GreenEnv "."))
  (GreenEnv-open env)
 
  ;;(gtk-signal-connect cmd-entry "insert_text" cmd-entry-insert-text)
  (gtk-signal-connect cmd-entry "activate" ( lambda()
     ;;(gtk-statusbar-push status-bar )
     ( let (
        (action (try-cmd commands (car-word (gtk-entry-get-text cmd-entry)))))
       (case action
        ((1) (load-table (cdr-word (gtk-entry-get-text cmd-entry))))
        ((2) (if current-table
                (begin
	              (add-row (cdr-word (gtk-entry-get-text cmd-entry)) (Table-new-row current-table) 0)
	              (load-table (Table-get-name current-table)))))
        ((3) (load-table (cdr-word (gtk-entry-get-text cmd-entry))))))))

  (gtk-widget-show-all window)
  (gtk-widget-grab-focus cmd-entry)
  (gtk-standalone-main window)
  (display "after gtk-standalone-main")))
  
(greendb-app) 
