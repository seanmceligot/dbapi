

(define browser-set-clist-titles 
 (lambda (clist schema n-columns i)
	(if (< i n-columns)
	 (begin 
		(gtk-clist-set-column-title clist i (Schema-get-name schema i)) 
        (gtk-clist-set-column-auto-resize clist i #t)
		(set! i (+ 1 i))
		(browser-set-clist-titles clist schema n-columns i)))))

(define show-col
  (lambda (row colno row-vector)
		(vector-set! row-vector colno (Row-to-string-n row colno))))

(define show-row 
 (lambda (clist row colno row-vector)
    (if (< colno (Row-size row))
    (begin
       (show-col row colno row-vector)
       (show-row clist row (+ 1 colno) row-vector)) 
    (begin
      (display row-vector) 
      (gtk-clist-append clist row-vector)))))


(define browser-show-rows 
  (lambda (clist table row index-name)
    (if (not (null? row))
     (begin
      (show-row clist row 0 (make-vector (Row-size row)))
      (browser-show-rows clist table (Table-next table row index-name) index-name)))))

