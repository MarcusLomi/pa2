FLAGS= -Wall -g 
CC= gcc

all: calc.c calc.h format.c format.h
	$(CC) -Wall -g calc.c -o calc
	$(CC) -Wall -g format.c -o format

calc: calc.c calc.h
	$(CC) -Wall -g calc.c -o calc

format: format.c format.h
	$(CC) -Wall -g format.c -o format

clean: 
	$(RM) *.o *.exe