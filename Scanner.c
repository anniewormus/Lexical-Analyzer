// COP3402
// 10.22.2020 - Andrea Wormus
// This code demonstrates a functioning compiler for the PL/0 language

#include <stdio.h>
#include <stdlib.h>

int main(){

    //read input

    
}
char *readFile(char *fileName){
    FILE *input = fopen(fileName, "r");
    char *code;
    size_t n = 0;
    int c;

    //checks for error opening file
    if (input == NULL)
        return NULL; 

    code = malloc(1000);

    while ((c = fgetc(input)) != EOF)
    {
        code[n++] = (char) c;
    }

    // don't forget to terminate with the null character
    code[n] = '\0';        

    return code;
}