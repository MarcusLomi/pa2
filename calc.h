#ifndef CALC_H_INCLUDED
#define CALC_H_INCLUDED

/*
 *@author Marcus A. Lomi
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "calc.h"
int formatCheck(char* s);
int toDecimalConversion(char* s);
char *decimalToOut(int i,int rad);
int numPow(int a, int b);
int subtract(int a, int b);
int add(int a, int b);
char *strrev(char *string);

#endif // CALC_H_INCLUDED
