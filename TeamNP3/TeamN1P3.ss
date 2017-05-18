;(define (not_main a b)
 ; (display 5)
  ;(newline)
;)

(define (multTest)
	(* 7 2)
	)

(define (plusTest n)
	(+ n 4 6)
	)

(define (plusMultTest n)
	(+ (* n 17) n (* 8 92))
	(+ 2 2)
	(+ n 4 6)
	)

(define (ifstmt a b)
	(if(< a b)
		a
		b
		)
	(if(>= a b)
		b
		)
	)

(define(funcAll a b c)
	(plusTest a)
	)

(define (predCheck b)
	(if (null? b)
		b
		)
	(if (not (list? b))
		7
		)
	)

(define (consTest a)
	(cons 'abcxyz '(1 2 3 4 5))
	)

(define (coutTest)
	(display (plusTest 2))
	)

(define (listopTest mylist)
	(cdr '(a b c))
	(cdr '(d e f))
	(car (cdr mylist))
	)

(define (main)
	)
