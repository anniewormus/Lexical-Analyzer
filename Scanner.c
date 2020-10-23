// COP3402
// 10.22.2020 - Andrea Wormus
// This code demonstrates a functioning compiler for the PL/0 language

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct for token types
typedef enum { 
nulsym = 1, identsym, numbersym, plussym, minussym,
multsym,  slashsym, oddsym, eqsym, neqsym, lessym, leqsym,
gtrsym, geqsym, lparentsym, rparentsym, commasym, semicolonsym,
periodsym, becomessym, beginsym, endsym, ifsym, thensym, 
whilesym, dosym, callsym, constsym, varsym, procsym, writesym,
readsym , elsesym } token_type;

typedef struct{
    token_type tokenVal;
    int kind;
    int numVal;
    char varname[10];      //in slides
}tokenStruct;

//array for reserved words names
char* reservedWords[] = {"const", "var", "procedure", "call", "begin", "end", "if", "then", "else", "while", "do", "read", "write", "odd"};

// //array for internal representation of reserved words
// int  wsym[] =  {beginsym, callsym, constsym, dosym, elsesym, endsym, ifsym, oddsym, procsym, readsym, thensym, varsym, whilesym, writesym};

//array for special symbols
char specialSyms[] = {'+', '-', '*', '/', '(', ')', '=', ',', '.', '<', '>', ';', ':'};

tokenStruct lexemeList[3000];   //array of token structs
int lexcount = 0;

int main(){

    int peek = 0;
    //get file name from user input
    char fileName[25];
    printf("What is your input file called? ");
    scanf("%s", fileName);

    //read input
    FILE *input = fopen(fileName, "r");

    //stores each character in file
    int c = fgetc(input);

    while (c != EOF){
        //ignore tabs, white spaces, and newlines
        if(iscntrl(c) || isspace(c)){
            c = fgetc(input);
           // peek = 0;
           continue;

        }else if(isalpha(c)){
            int length = 0;
            char word[12] = {0};    //12 chars is error identifier length

            word[0] = c;
            length++;
            peek = 1;
            c = fgetc(input);
            while(isalpha(c) || isdigit(c)){
               //errors out if identifier is longer than 11 characters
                if(length > 10){
                    printf("\nERROR: Name too long.");
                    while(isalpha(c)||isdigit(c)){
                        c = fgetc(input);
                    }
                    peek = 0;
                    break;
                }
                word[length] = c;
                c = fgetc(input);
                length++;
                if(iscntrl(c) || isspace(c)){
                    break;
                }

            }
            //check to see if word is a reserve word 
            int i = 0;
            int reswordcheck = 100;
            for(i; i < 14; i++){
                if(strcmp(word, reservedWords[i]) == 0){
                    reswordcheck = i;
                }
            }
            switch(reswordcheck){
                case 0:
                    lexemeList[lexcount].tokenVal = constsym;
                    lexemeList[lexcount].kind = 1;
                    break;
                case 1:
                    lexemeList[lexcount].tokenVal = varsym;
                    lexemeList[lexcount].kind = 2;
                    break;
                case 2:
                    lexemeList[lexcount].tokenVal = procsym;
                    lexemeList[lexcount].kind = 3;
                    break;
                case 3:
                    lexemeList[lexcount].tokenVal = callsym;
                    break;
                case 4:
                    lexemeList[lexcount].tokenVal = beginsym;
                    break;
                case 5:
                    lexemeList[lexcount].tokenVal = endsym;
                    break;
                case 6:
                    lexemeList[lexcount].tokenVal = ifsym;
                    break;
                case 7:
                    lexemeList[lexcount].tokenVal = thensym;
                    break;
                case 8:
                    lexemeList[lexcount].tokenVal = elsesym;
                    break;
                case 9:
                    lexemeList[lexcount].tokenVal = whilesym;
                    break;
                case 10:
                    lexemeList[lexcount].tokenVal = dosym;
                    break;
                case 11:
                    lexemeList[lexcount].tokenVal = readsym;
                    break;
                case 12:
                    lexemeList[lexcount].tokenVal = writesym;
                    break;
                case 13:
                    lexemeList[lexcount].tokenVal = oddsym;
                    break;
                default:
                    lexemeList[lexcount].tokenVal = identsym;
                    strcpy(lexemeList[lexcount].varname, word);
                    break;
            }
            lexcount++;

        }else if(isdigit(c)){
            int digit = c - '0';
            int digLength = 1;
            c = fgetc(input);
            peek = 1;

            while(isdigit(c)){
                
                if(digLength > 5){
                    printf("\nERROR: Number too long");
                     while (isdigit(c)) {
                        c = fgetc(input);
                    }
                    break;
                }
                digit = 10 * digit + (c - '0');
                digLength++;
                c = fgetc(input);
            }

            //throws error if the variable starts with a number
            if(isalpha(c)){
                printf("ERROR: Variable does not start with letter");
               c = fgetc(input);
                while(isalpha(c)||isdigit(c)){
                    c = fgetc(input);
                }
            }
                lexemeList[lexcount].numVal = digit;
                lexemeList[lexcount].tokenVal = numbersym;
                lexcount++;
        }else{
            //if the character is a special symbol
            peek = 0;
            int i;
            int sym;
            for(i = 0; i < 13; i++){
                if(c == specialSyms[i]){
                    sym = i;
                }
            }
            switch(sym){
                case 0:
                    lexemeList[lexcount].tokenVal = plussym;
                    lexcount++;
                    break;
                case 1:
                    lexemeList[lexcount].tokenVal = minussym;
                    lexcount++;
                    break;
                case 2:
                    lexemeList[lexcount].tokenVal = multsym;
                    lexcount++;
                    break;
                case 3:
                    c = fgetc(input);
                    peek = 1;
                    if(c == '*'){
                        c = fgetc(input);
                        int loop = 1;
                        peek = 0;
                        while(loop){
                            if(c == '*'){
                                c = fgetc(input);
                                if(c == '/'){
                                    loop = 0;
                                }
                            }else{
                                c = fgetc(input);
                            }
                        }
                    }else{      //just a slash. not a comment
                        lexemeList[lexcount].tokenVal = slashsym;
                        lexcount++;
                    }
                    break;
                case 4:
                    lexemeList[lexcount].tokenVal = lparentsym;
                    lexcount++;
                    break;
                case 5:
                    lexemeList[lexcount].tokenVal = rparentsym;
                    lexcount++;
                    break;
                case 6:
                    lexemeList[lexcount].tokenVal = eqsym;
                    lexcount++;
                    break;
                case 7:
                    lexemeList[lexcount].tokenVal = commasym;
                    lexcount++;
                    break;
                case 8:
                    lexemeList[lexcount].tokenVal = periodsym;
                    lexcount++;
                    break;
                case 9:
                    c = fgetc(input);
                    peek = 1;
                    if(c == '>'){
                        lexemeList[lexcount].tokenVal = neqsym;
                        peek = 0;
                    }else if(c == '='){
                        lexemeList[lexcount].tokenVal = leqsym;
                        peek = 0;
                    }else{
                        lexemeList[lexcount].tokenVal = lessym;
                    }
                    lexcount++;
                    break;
                case 10:
                    c = fgetc(input);
                    peek = 1;
                    if(c == '='){
                        lexemeList[lexcount].tokenVal = geqsym;
                        peek = 0;
                    }else{
                        lexemeList[lexcount].tokenVal = gtrsym;
                    }
                    lexcount++;
                    break;
                case 11:
                    lexemeList[lexcount].tokenVal = semicolonsym;
                    lexcount++;
                    break;
                case 12:
                    c = fgetc(input);
                    if(c == '='){
                        lexemeList[lexcount].tokenVal = becomessym;
                        lexcount++;
                    }else{
                        printf("ERROR: Invalid symbols");
                    }
                    break;
                default:
                    printf("ERROR: Invalid symbols");
                    break;
            }
        }
        if(peek == 0){
            c = fgetc(input);
        }
        
    }
        int i = 0;
        for(i; i < lexcount; i++){
            printf("%d ", lexemeList[i].tokenVal);
            if(lexemeList[i].tokenVal == 2){
                printf("%s ", lexemeList[i].varname);
            }else if(lexemeList[i].tokenVal == 3){
                printf("%d ", lexemeList[i].numVal);
            }
        }
}