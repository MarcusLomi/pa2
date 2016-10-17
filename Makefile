FLAGS= -Wall -g 
calc: calc.c calc.h
	gcc -Wall -g calc.c -o calc

format: format.c format.h
	gcc -Wall -g format.c -o format

Clean:
	rm *o
