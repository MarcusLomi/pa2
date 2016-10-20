#ifndef FORMAT_H_INCLUDED
#define FORMAT_H_INCLUDED
<<<<<<< HEAD

=======
/*
 *@author Marcus A. Lomi
 */
static void
get_float_digit( float x, char * digit, int * pow10, float * remainder );
static void
append( char * s, char c );
void intToDecASCII(int pow10, char *exponent );
void floatToASCII( float x, char * output );
>>>>>>> 0be4e70aa7b95d52988fbdc09560b1641f62f1ac
char *strrev(char *str);
int numPow(int a, int b);
char *decimalToOut(int i,int rad);
int formatCheck(char* s);
int toDecimalConversion(char* s);

#endif // FORMAT_H_INCLUDED
