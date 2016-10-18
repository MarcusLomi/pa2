#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
        printf("\nERROR: Improper number format. \nPlease input a 32-bit binary sequence");
        return 1;
    }

    while(s[c]=='0'||s[c]=='1'){
        c+=1;
    }

    if(s[c]=='\0'){
        return 0;
    }
    else{
        printf("\nERROR: Improper number format. Invalid characters in 32-bit binary string");
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
        printf("\nYOU HAVE A NEGATIVE \nBEFORE THE SCREW UP RESULT IS:%d",result);
        result=-2147483647+result;
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

    if(strcmp(str,"int")==0){
        num1=toDecimalConversion(argv[1]);
        printout=decimalToOut(num1,10);
        printf("\n%s",printout);
    }


    return 0;

}
