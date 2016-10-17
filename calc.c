#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "calc.h"

/*
 *@author Marcus A. Lomi
 */

char *strrev(char *str)
{
      char *p1, *p2;

      if (! str || ! *str)
            return str;
      for (p1 = str, p2 = str + strlen(str) - 1; p2 > p1; ++p1, --p2)
      {
            *p1 ^= *p2;
            *p2 ^= *p1;
            *p1 ^= *p2;
      }
      return str;
}

/*
 * add adds a to b
 */

int add(int a, int b){
    int c = a+b;
    return c;
}

/*
 * subtracts b from a
 */

int subtract(int a, int b){
    int c = a-b;
    return c;
}

/*
 * numPow raises the given number (a) to the power (b)
 */

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

/*
 * decimalToOut takes the decimal integer generated from the input string of numbers
 * and converts it to the desired output string using the desired base (rad).
 *
 * If the number is negative, for ease of use, the algorithm makes the integer positive
 * before generating the ascii characters to put into the string so that the algorithm remains
 * simple.
 */

char *decimalToOut(int i,int rad){
    char *result;
    char hexChar[6]={'a','b','c','d','e','f'};  //saves the letter values for hexadecimal numbers 10-15
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
        if(remain>9){
            result[counter] = hexChar[remain%10];
        }
        else{
            result[counter] = (i%rad) + '0' ;
        }
        i=i/rad;
        counter++;
    }
    result[counter]='\0';
    strrev(result);

    return result;

}

/*
 * toDecimalConversion takes the input string and converts it from its input base
 * into decimal form.
 *
 * No extra checks for proper format have to be made at this point
 * because the code has already checked for errors in number format.
 */

int toDecimalConversion(char* s){
    char base;      //Saves the the char for the base of the input number
    int result;     //Output of the function
    int end=0;      //Saves the index of the null terminator at the end of the string
    int start=0;    //Saves the index for the start of the digit portion of the number string.
    int c=0;        //Counter for the loop
    int pos = 0;    //Used to multiply digits based on their placement to attain proper significance of figures

    end=strlen(s);
    result=0;

    if(s[0]=='-'){
        start=2;
        base=s[1];
    }
    else{
        start=1;
        base=s[0];
    }

    /*Loops for changing the number string from any base into a decimal integer.
      Traverses through string backwards and adds to the integer based on significance*/
    if(base=='d'){
        for(c=start;c<end;c++){
            result=(result * 10)+(s[c]%48);
            //printf("\nResult is: %d ",result);
            //printf("\nAdding: %d",(s[c]%48));
            pos++;
        }
    }
    else if(base=='b'){
        for(c=end-1;c>=start;c--){
            result += numPow(2,pos)*(s[c]%48);
            //printf("\nResult is: %d ",result);
            //printf("\nAdding: %d",(s[c]%48));
            pos++;
        }
    }
    else if(base=='o'){
        for(c=end-1;c>=start;c--){
            result += numPow(8,pos)*(s[c]%48);
            //printf("\nResult is: %d ",result);
            //printf("\nAdding: %d",(s[c]%48));
            pos++;
        }
    }
    else if(base=='x'){
        for(c=end-1;c>=start;c--){
            if(isdigit(s[c])){
                result += numPow(16,pos)*(s[c]%48);
            }
            if(isalpha(tolower(s[c]))){
                result += numPow(16,pos)*(tolower(s[c])%87);
            }

            //printf("\nResult is: %d ",result);
            //printf("\nAdding: %d",(s[c]%48));
            pos++;

        }

    }

    if(s[0]=='-'){
        result-=(result*2);
    }

    return result;
}

/*
 * formatCheck, checks incoming number strings for format errors
 */

int formatCheck(char* s){

    int c=1;     //Counter for keeping track of the index
    char base;   //Saves the base identifier character at the beginning of the string

    if(strlen(s)<2){
        printf("\nERROR: Insufficient number of characters for number argument. <-?(b|o|d|x)d,dn-1....d1,d1>");
        return 1;
    }
    else if(s[0]=='-'){
        if(s[1]!='d'&&s[1]!='b'&&s[1]!='o'&&s[1]!='x'){
            printf("\nERROR:1 Improper number format. <-?(b|o|d|x)d,dn-1....d1,d1>");
            return 1;
        }
        c+=1;
    }
    else if(s[0]!='d'&&s[0]!='b'&&s[0]!='o'&&s[0]!='x'){
        printf("\nERROR:2 Improper number format. <-?(b|o|d|x)d,dn-1....d1,d1>");
        return 1;
    }
    base=s[c-1];
    if(base=='d'){
        while(isdigit(s[c])){
           c+=1;
        }
    }
    else if(base=='b'){
        while(s[c]=='0'||s[c]=='1'){
            c+=1;
        }
    }
    else if(base=='x'){
        while(isalnum(s[c])){
            if(isalpha(s[c])){
                if(tolower(s[c])!='a'&&tolower(s[c])!='b'&&tolower(s[c])!='c'&&tolower(s[c])!='d'&&tolower(s[c])!='e'&&tolower(s[c])!='f'){
                   fprintf(stderr,"\nERROR:2 Improper number format.\nLetters out of hex range <-?(b|o|d|x)d,dn-1....d1,d1>");
                   return 1;
                }
            }
           c+=1;
        }
    }
    else if(base=='o'){
        while(isdigit(s[c])){
            if(s[c]=='8'||s[c]=='9'){
                fprintf(stderr,"\nERROR: Improper number format.\nNumbers out of octal range <-?(b|o|d|x)d,dn-1....d1,d1>");
                return 1;
            }
            c+=1;
        }
    }
    if(s[c]=='\0'){
        return 0;
    }
    else{
        printf("\nERROR:3 Improper number format. at index%d <-(b|o|d|x)d,dn-1....d1,d1>",c);
        return 1;
    }
    return 0;
}

int main(int argc, char **argv){
    char *num1;     // copy of the string value for Num 1 entered in the command line
    char *num2;     // copy of the string value for Num 2 entered in the command line
    int dNum1;      // decimal version of the input number 1
    int dNum2;      // decimal version of the input number 2
    int decResult;  // result of the operation done on dNum1 and dNum2
    char* printout; // pointer to final printout string

    /*Catching errors with improper number of args or bad arg format*/
    if(argc!=5){
        fprintf(stderr,"\nERROR:\nYou don't have the correct number of args. \n The correct format is <op> <num1> <num2> <base>\n");
        return 0;
    }
    if((*argv[1]!='+'&&*argv[1]!='-')||strlen(argv[1])!=1){
        fprintf(stderr,"ERROR: \nBad format: The first argument is not a \'+\' or a \'-\'");
        return 0;
    }
    if(strlen(argv[4])!=1){
        fprintf(stderr,"ERROR: \nBad format: Length of arg for output base should be 1 letter <d/o/x/b>");
        return 0;
    }

   /*Allocating space for string copies of argv[2] and argv[3]*/
    num1=malloc(strlen(argv[2])+1);
    num2=malloc(strlen(argv[3])+1);
    strcpy(num1,argv[2]);
    strcpy(num2,argv[3]);

    /*Checking for formatting errors in number inputs*/
    if(formatCheck(num1)==1||formatCheck(num2)==1){
        return 0;
    }

    /*Takes the strings num1 and num2 and generates decimal integers from them*/
    dNum1= toDecimalConversion(num1);
    free(num1);
    dNum2= toDecimalConversion(num2);
    free(num2);

    if(*argv[1]=='+'){
        decResult=add(dNum1,dNum2);
    }
    else if(*argv[1]=='-'){
        decResult=subtract(dNum1,dNum2);
    }

    /*If the result of the operation is zero, there is no need to make any more calculations*/
    if(decResult==0){
        printf("%s0",argv[4]);
        return 0;
    }

    /*Switcher for generating a proper string dependent on the output base <d/o/b/x>*/
    switch(*argv[4]){
        case 'd':
            printout=decimalToOut(decResult,10);
            break;
        case 'b':
            printout=decimalToOut(decResult,2);
            break;
        case 'x':
            printout=decimalToOut(decResult,16);
            break;
        case 'o':
            printout=decimalToOut(decResult,8);
            break;
    }

    if(decResult<0){
        printf("-%s%s",argv[4],printout);
    }
    else{
        printf("%s%s",argv[4],printout);
    }

    return 0;
}
