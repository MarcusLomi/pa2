#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Convert IEEE 32-bit floating point to printable ASCII string

// input: x is the 32-bit input.
// output:  digit is the output ASCII character
// output:  pow10 is the original pre-normalization power of 10.
// output: remainder is x after subtracting the higi-digit value

static void
get_float_digit( float x, char * digit, int * pow10, float * remainder )
{
	int			p10;

	if ( x == 0.0 )
	{
		*digit = '0';			// digit is always '0'
		*pow10 = 0;
		*remainder = 0.0;
	}
	else
	{
		*pow10 = 0;			// start with 10^0
		while ( x >= 10.0 )		// reduce
		{
			x /= 10.0;		// large values get smaller
			*pow10 += 1;
		}
		while ( x < 1.0 )		// increase
		{
			x *= 10.0;		// small values get larger
			*pow10 -= 1;
		}
		*digit = '0';
		do {				// 10.0 > x >= 1.0
			x -= 1.0;
			*digit += 1;		// digit is always non-'0'zero
		} while ( x >= 1.0 );
		p10 = 0;
		while ( p10 > *pow10 )		// leading digit is now removed from x
		{
			x /= 10;
			p10 -= 1;
		}
		while ( p10 < *pow10 )
		{
			x *= 10;
			p10 += 1;
		}
		*remainder = x;
	}
}

// Improve efficiency by adding more while loops to handle larger powers of 10, e.g. :
// while ( x >= 1e1024 ) { x /= 1e0124; pow10 += 1024; }
// while ( x >= 1e512 ) { x /= 1e512; pow10 += 512; }
// ...
// while ( x >= 10.0 ) { x /= 10.0 ; pow10 += 1; }
// And
// while ( x < 1.0 ) { x *= 10; pow10 -= 1; }
// ...
// while ( x < 1e-512 ) { x *= 1e512; pow10 -= 512; }
// while ( x < 1e-1024 ) { x *= 1e1024; pow10 -= 1024; }

static void
append( char * s, char c )
{
	char		buf[2];

	buf[0] = c;
	buf[1] = '\0';
	strcat( s, buf );
}

union Number {
	int	i;
	float	f;
};

void intToDecASCII(int pow10, char *exponent ){
    int i;
    for(i=0;i<10;i++){
        exponent[i]='0';
    }

    int counter=0;
    //printf("\nFUCKING POW10: %d\n",pow10);
    /*Makes negative input integers positive*/
    if(pow10<0){
        exponent[counter]='-';
        //append(exponent,'-');
        counter++;
        pow10-=(pow10*2);
    }
    //printf("\nFUCKING POW10: %d\n",pow10);

    /*Adds the character value for the remainder of the modulo operation to the output string*/
    while(pow10!=0){

        //append(exponent,(pow10%10) + '0');
        exponent[counter]=(pow10%10)+'0';
        //printf("\nAPPENDING%d\n",(pow10%10)+'0');
        pow10=pow10/10;
        counter++;
    }
    exponent[counter]='\0';

    //printf("\nEXPONENT: %s \n",exponent);
}

void
floatToASCII( float x, char * output )
{
	char		c;
	int		pow10, p10, plast;
	int		i;
	float		remainder;
	char		exponent[10];
	union Number	a;
	unsigned int	biasedExp;
	unsigned int	mantissa;
	int		sign;

	a.f = x;
	biasedExp = a.i >> 23 & 0x000000ff;
	mantissa = a.i & 0x007fffff;
	sign = a.i >> 31;
	//printf( "BKR x is %g.  biasedExp is %x  mantissa is %08x  sign is %d\n", x,
		//biasedExp, mantissa, sign );
	if ( biasedExp == 0xff )
	{
		if ( mantissa == 0 )
		{
			if ( sign != 0 )
			{
				strcpy( output, "-inf" );
		printf( "BKR returning from file %s line %d\n", __FILE__, __LINE__ );
				return;
			}
			else
			{
				strcpy( output, "+inf" );
		printf( "BKR returning from file %s line %d\n", __FILE__, __LINE__ );
				return;
			}
		}
		else
		{
			if ( sign != 0 )
			{
				strcpy( output, "-NaN" );
		printf( "BKR returning from file %s line %d\n", __FILE__, __LINE__ );
				return;
			}
			else
			{
				strcpy( output, "+NaN" );
		printf( "BKR returning from file %s line %d\n", __FILE__, __LINE__ );
				return;
			}
		}
	}
	output[0] ='\0';
	if ( x < 0.0 )
	{
		append( output, '-' );
		x = -x;					// make x positive
	}
	get_float_digit( x, &c, &pow10, &remainder );
	append( output, c );
	append( output, '.' );
	x = remainder;
	plast = p10 = pow10;			// pow10 set by get_float_digit()
	for ( i = 1 ; i < 7 ; i++ )		// 7 significant digits in 32-bit float
	{
		get_float_digit( x, &c, &p10, &remainder );
		if ( (plast - p10) > 1 )
		{
			append( output, '0' );	// fill in zero to next nonzero digit
			plast -= 1;
		}
		else
		{
			append( output, c );
			x = remainder;
			plast = p10;
		}
	}
	if ( pow10 < 0 )		// negative exponent
	{
		exponent[0] = 'e';
		intToDecASCII( pow10, exponent+1 );
	}
	else if ( pow10 < 10 )		// positive single-digit exponent
	{
		exponent[0] = 'e';
		exponent[1] = '+';
		exponent[2] = '0';
		intToDecASCII( pow10, exponent+3 );
	}
	else				// positive multi-digit exponent
	{
		exponent[0] = 'e';
		exponent[1] = '+';
		intToDecASCII( pow10, exponent+2 );
	}
	strcat( output, exponent );
}

char *strrev(char *str){
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2){
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

int numPow(int a, int b){

    int result=0;
    result=a;
    int i=0;
    if(b==0){
        return 1;
    }

    for(i=1;i<b;i++){
        result=result*a;
    }

    return result;
}
char *decimalToOut(int i,int rad){
    char *result;
    result=(char*)malloc(200 * sizeof(char));   //allocates memory for a result string of size 200.
    int counter=0;                              //a counter to keep track of where the ascii chars will be inserted in the array
    int remain;                                 //saves the remainder of the modulo operation done on the input integer (i)

    /*Makes negative input integers positive*/
    if(i<0){
        i-=(i*2);
    }
    result[200]='\0';

    /*Adds the character value for the remainder of the modulo operation to the output string*/
    while(i!=0){
        remain=(i%rad);
        result[counter] = remain + '0' ;
        i=i/rad;
        counter++;
    }
    result[counter]='\0';
    strrev(result);

    return result;
}

int formatCheck(char* s){
    int c=0;

    if(strlen(s)!=32){
        fprintf(stderr,"\nERROR: Improper number format. \nPlease input a 32-bit binary sequence");
        return 1;
    }

    while(s[c]=='0'||s[c]=='1'){
        c+=1;
    }

    if(s[c]=='\0'){
        return 0;
    }
    else{
        fprintf(stderr,"\nERROR: Improper number format. Invalid characters in 32-bit binary string");
        return 1;
    }
    return 0;
}

int toDecimalConversion(char* s){
    int result;     //Output of the function
    int end=0;      //Saves the index of the null terminator at the end of the string
    int start=1;    //Saves the index for the start of the digit portion of the number string.
    int c=0;        //Counter for the loop
    int pos = 0;    //Used to multiply digits based on their placement to attain proper significance of figures

    end=strlen(s);
    result=0;

    for(c=end-1;c>=start;c--){
        result += numPow(2,pos)*(s[c]%48);
        pos++;
    }

    if(s[0]=='1'){
        result=result-2147483648;
    }

    return result;
}



int main(int argc, char** argv){


    char* printout;
    int num1;

    if(argc!=3){
        fprintf(stderr,"\nERROR:\nYou don't have the correct number of args.\nThe correct format is <input sequence> <type>\n");
        return 0;
    }
    char* str=argv[2];
    for(int i = 0; str[i]; i++){
        str[i] = tolower(str[i]);
    }
    if(strcmp(str,"int")!=0&&strcmp(str,"float")!=0){
        fprintf(stderr,"\nERROR: Invalid type. Must be either <int/float>");
        return 0;
    }
    if(formatCheck(argv[1])==1){
        return 0;
    }

    if(strcmp(argv[1],"10000000000000000000000000000000")==0){
        printf("-2147483648");
        return 0;
    }

    char * work = argv[1];

    union{
        int x;
        float y;
    }myU;

    int k=0;
    for(k=0;k<32;k++){
        switch(work[k]){
            case '0':
                myU.x=(myU.x<<1);
                break;
            case'1':
                myU.x=(myU.x<<1)+1;
                break;
        }

    }
    //printf("\nI HOPE THIS DA NUMBER :%d\n",myU.x);
    //printf("\nHERE DA FLOAT:%f\n",myU.y);

    //printf("\nDID IT WORK? :%f\n",y);
    char * floatOutPutString= malloc(32*sizeof(char));


    //printf("\nDID IT WORK? :%f\n",y);
    //printf("\nHEY YALL %s",floatOutPutString);

    num1=toDecimalConversion(argv[1]);

    printout=decimalToOut(num1,10);

    //char *output= malloc(200*sizeof(char));
    char * num=argv[1];

    if(strcmp(str,"int")==0){
        if(num[0]=='1'){
            printf("-%s",printout);
        }else{
            printf("%s",printout);
        }
    }
    else if(strcmp(str,"float")==0){
        if(num[0]=='1'){
            floatToASCII(myU.y,floatOutPutString);
            printf("%s",floatOutPutString);
        }else{
            floatToASCII(myU.y,floatOutPutString);
            printf("%s",floatOutPutString);
        }
    }

    return 0;

}
