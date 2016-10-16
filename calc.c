#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "calc.h"

outNum *getNum(int b){
    outNum *r = malloc(sizeof(outNum));
    r->a=b;
    return r;
}

int add(int a, int b){
    int c = a+b;
    return c;
}

int subtract(int a, int b){
    int c = a-b;
    return c;
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

char *decimalToBin(int i,int rad){
    char *result;
    char hexChar[6]={'a','b','c','d','e','f'};
    result=(char*)malloc(200 * sizeof(char));
    int counter=0;
    int remain;

    if(i<0){
        i-=(i*2);
        printf("\nI IS LESS THAN 0: %d",i);
    }

    printf("\nHERE DA COUNTER: ");

    result[200]='\0';

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

    //free(result);
    printf("\nHERE DA COUNTER: %d",counter);
    return result;

}

char *decimalToOctal(int i){
    //char* result[200];

    return NULL;
}

char *decimalToHex(int i){
    //char* result[200];

    return NULL;
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
    /*Loops for changing */
    if(base=='d'){
        for(c=start;c<end;c++){
            result=(result * 10)+(s[c]%48);
            printf("\nResult is: %d ",result);
            printf("\nAdding: %d",(s[c]%48));
            pos++;
        }
    }
    else if(base=='b'){
        for(c=end-1;c>=start;c--){
            result += numPow(2,pos)*(s[c]%48);
            printf("\nResult is: %d ",result);
            printf("\nAdding: %d",(s[c]%48));
            pos++;
        }
    }
    else if(base=='o'){
        for(c=end-1;c>=start;c--){
            result += numPow(8,pos)*(s[c]%48);
            printf("\nResult is: %d ",result);
            printf("\nAdding: %d",(s[c]%48));
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

            printf("\nResult is: %d ",result);
            printf("\nAdding: %d",(s[c]%48));
            pos++;

        }

    }

    if(s[0]=='-'){
        result-=(result*2);
    }

    return result;
}

/*
 *FormatCheck, checks incoming number strings for format errors
 */

int formatCheck(char* s){

    int c=1;     //Counter for keeping track of the index
    char base;   //saves the base identifier character at the beginning of the string

    if(strlen(s)<2){
        printf("\nERROR: Insufficient number of characters for number argument. <-(b|o|d|x)d,dn-1....d1,d1>");
        return 1;
    }
    else if(s[0]=='-'){
        if(s[1]!='d'&&s[1]!='b'&&s[1]!='o'&&s[1]!='x'){
            printf("\nERROR:1 Improper number format. <-(b|o|d|x)d,dn-1....d1,d1>");
            return 1;
        }
        c+=1;
    }
    else if(s[0]!='d'&&s[0]!='b'&&s[0]!='o'&&s[0]!='x'){
        printf("\nERROR:2 Improper number format. <-(b|o|d|x)d,dn-1....d1,d1>");
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
                   printf("\nERROR:2 Improper number format.\nLetters out of hex range <-(b|o|d|x)d,dn-1....d1,d1>");
                   return 1;
                }
            }
           c+=1;
        }
    }
    else if(base=='o'){
        while(isdigit(s[c])){
            if(s[c]=='8'||s[c]=='9'){
                printf("\nERROR:2 Improper number format.\nNumbers out of octal range <-(b|o|d|x)d,dn-1....d1,d1>");
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
    char *num1; // copy of the string value for Num 1 entered in the command line
    char *num2; // copy of the string value for Num 2 entered in the command line
    int dNum1;  // decimal version of the input number 1
    int dNum2;  // decimal version of the input number 2
    int decResult; // result of the operation done on dNum1 and dNum2
    //char operation; //addition or subtraction operation being performed on the numbers
    int hey = 0;
    hey='a'%87;
    printf("\nHere:%d",hey);
    if(argc!=5){
        printf("\nERROR:\nYou don't have the correct number of args. \n The correct format is <op> <num1> <num2> <base>\n");
        return 0;
    }
    if((*argv[1]!='+'&&*argv[1]!='-')||strlen(argv[1])!=1){
        printf("ERROR: \nBad format: The first argument is not a \'+\' or a \'-\'");
        return 0;
    }
    if(strlen(argv[4])!=1){
        printf("ERROR: \n Bad format: Length of arg for output base should be 1 letter <d/o/x/b>");
        return 0;
    }
    printf("Here is the length of the last arg: %d\n",strlen(argv[4]));

   /*Allocating space for strings*/
    num1=malloc(strlen(argv[2])+1);
    num2=malloc(strlen(argv[3])+1);
    strcpy(num1,argv[2]);
    strcpy(num2,argv[3]);

    /*Checking for formatting errors in number inputs*/
    if(formatCheck(num1)==1||formatCheck(num2)==1){
        return 0;
    }

    dNum1= toDecimalConversion(num1);
    dNum2= toDecimalConversion(num2);

    if(*argv[1]=='+'){
        decResult=add(dNum1,dNum2);
    }
    else if(*argv[1]=='-'){
        decResult=subtract(dNum1,dNum2);
    }

    printf("\nHERE IS THE RESULT BEFORE CONVERTING: %d",decResult);

    char* printout;

    switch(*argv[4]){
        case 'd':
            printout=decimalToBin(decResult,10);
            break;
        case 'b':
            printout=decimalToBin(decResult,2);
            break;
        case 'x':
            printout=decimalToBin(decResult,16);
            break;
        case 'o':
            printout=decimalToBin(decResult,8);
            break;
    }


    printf("\nHERE IT IS: %s",printout);
    printf("\nSIZEOF: %d",strlen(printout));

    if(decResult<0){
        char finalOut[strlen(printout)+2];
        finalOut[0]='-';
        finalOut[1]=*argv[4];
        strcat(finalOut, printout);
        printf("\n%s",finalOut);
    }
    else{
        char finalOut[strlen(printout)+1];
        finalOut[0]=*argv[4];
        strcat(finalOut, printout);
        printf("\n%s",finalOut);
    }


    return 0;
}
