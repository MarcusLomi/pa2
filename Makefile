FLAGS= -Wall -g 
calc: calc.c calc.h
	gcc -Wall -g calc.c -o calc

Clean:
	rm *o
