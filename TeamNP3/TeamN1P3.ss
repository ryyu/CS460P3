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
	;;(if(>= a b)
	;;	b
	;;	)
	)

(define(funcAll a b c)
	(plusTest a)
	)

(define (predCheck b)
	(if (null? b)
		b	
		(if (not (list? b))
			7
			(if (symbol? b)
				8
				(if (> b 8)
					9
					(+ 2 2)
					)
				)
			)
	)
)

(define (consTest lst)
	(cons lst '(1 2 3 4 5))
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
	(display 'Hello_world)
	(newline)
	(display (multTest))
	(newline)
	(display (plusTest 5))
	(newline)
	(display (plusMultTest 17))
	(newline)
	(display (ifstmt 1 3))
	(newline)
	(display (funcAll 28 31 34))
	(newline)
	(display (predCheck '()))
	(newline)
	(display (consTest '(a b c)))
	(newline)
	(coutTest)
	(newline)
	(display (listopTest '(a b c)))
	)

;;(main)