FLAGS= -Wall -g 

all: calc.c calc.h format.c format.h
	gcc -Wall -g calc.c -o calc
	gcc -Wall -g format.c -o form

calc: calc.c calc.h
	gcc -Wall -g calc.c -o calc

format: format.c format.h
	gcc -Wall -g format.c -o form

clean:
	rm format.o calc.o 
