#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "calc.h"

test *testCreate(int b){
    test *r = malloc(sizeof(test));
    r->a=b;
    return r;
}


/*
 *FormatCheck, checks incoming number strings for format errors
 */

int formatCheck(char* s){

    /*Counter for keeping track of the index*/
    int c=1;    //Counter for keeping track of the index
    char base;   //saves the base identifier character at the beginning of the string

    if(strlen(s)<3){
        printf("\nERROR: Insufficient number of characters for number argument. <-(b|o|d|x)d,dn-1....d1,d1>");
        return 1;
    }
    else if(s[0]=='-'){
        if(s[1]!='d'&&s[1]!='b'&&s[1]!='o'&&s[1]!='x'){
            printf("\nERROR:1 improper number format. <-(b|o|d|x)d,dn-1....d1,d1>");
            return 1;
        }
        c+=1;
    }
    else if(s[0]!='d'&&s[0]!='b'&&s[0]!='o'&&s[0]!='x'){
        printf("\nERROR:2 improper number format. <-(b|o|d|x)d,dn-1....d1,d1>");
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
                   printf("\nERROR:2 improper number format. Letters out of hex range <-(b|o|d|x)d,dn-1....d1,d1>");
                   return 1;
                }
            }
           c+=1;
        }
    }
    else if(base=='o'){

    }
    if(s[c]=='\0'){
        return 0;
    }
    else{
        printf("\nERROR:3 improper number format. at index%d <-(b|o|d|x)d,dn-1....d1,d1>",c);
        return 1;
    }

    return 0;
}


int main(int argc, char **argv){
    char *num1; // copy of the string value for Num 1 entered in the command line
    char *num2; // copy of the string value for Num 2 entered in the command line

    if(argc!=5){
        printf("\nERROR:\nYou don't have the correct number of args. \n The correct format is <op> <num1> <num2> <base>\n");
        return 0;
    }
    if(*argv[1]!='+'&&*argv[1]!='-'){
        printf("ERROR: \nBad format: The first argument is not a \'+\' or a \'-\'");
        return 0;
    }
    printf("Here is the length of the last arg: %d\n",strlen(argv[4]));
    num1=malloc(strlen(argv[2])+1);
    num2=malloc(strlen(argv[2])+1);
    //int i=0;
    //for(i=0;i<strlen(num1);i++){
        //num1[i]=0;
    //}
    strcpy(num1,argv[2]);
    strcpy(num2,argv[3]);

    if(formatCheck(num1)==1||formatCheck(num2)==1){
        return 0;
    }

    //char *num1[strlen(argv[2])+1];
    //char *num2[strlen(argv[3])+1];

    num1[1]='9';
    printf("%s \nargv:%s",num1,argv[2]);
    test *a = testCreate(5);
    printf("\nHEY THERE: %d",a->a);





    return 0;
}
