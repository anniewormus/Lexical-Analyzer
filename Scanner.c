// COP3402
// 10.22.2020 - Andrea Wormus
// This code demonstrates a functioning compiler for the PL/0 language

#include <stdio.h>
#include <stdlib.h>

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
    int numVal;
    char name[10];
}tokenStruct;

//array for reserved words names
char* reservedWords[] = {"const", "var", "procedure", "call", "begin", "end", "if", "then", "else", "while", "do", "read", "write", "odd"};
//array for internal representation of reserved words
int  wsym[] =  {beginsym, callsym, constsym, dosym, elsesym, endsym, ifsym, oddsym, procsym, readsym, thensym, varsym, whilesym, writesym};
//array for special symbols
char specialSyms = {'+', '-', '*', '/', '(', ')', '=', ',', '.', '<', '>', ';', ':'};

tokenStruct lexemeList[3000];
int lexemeCounter = 0;

int main(){

    //get file name from user input
    char fileName[25];
    printf("What is your input file called? ");
    scanf("%s", fileName);

    //read input
    FILE *input = fopen(fileName, "r");

    //checks for error opening file
    if (input == NULL) return NULL; 

    int c = fgetc(input);

    while (c != EOF){
        //ignore tabs, white spaces, and newlines
        if(iscntrl(c) || isspace(c)){
            continue;
        }
        //ignore comments
        if(c == '/'){
            c = fgetc(input);
            if(c == '*'){
                while(c != '*'){
                    c = fgetc(input);
                }
                if(c == '*' && (c = fgetc(input)) == '/'){
                    continue;
                }
            }
        }
        if(isalpha(c)){
            int length = 0;
            char word[12] = {0};    //12 chars is error identifier length

            word[0] = c;
            c = fgetc(input);
            while(isalpha(c) || isdigit(c)){
               
               //errors out if identifier is longer than 11 characters
                if(length > 10){
                    printf("\nERROR: Name too long.");
                    break;
                }
                word[length] = c;
                c = fgetc(input);
                length++;

            }
            //check to see if word is a reserve word 
            int i = 0;
            int reswordcheck;
            for(i; i < 14; i++){
                if(strcmp(word, reservedWords[i]) == 0){
                    reswordcheck = i;
                }
            }
            switch(reswordcheck){
                case 0:
                    lexemeList[lexemeCounter].tokenVal = constsym;
                    break;
                case 1:
                    lexemeList[lexemeCounter].tokenVal = varsym;
                    break;
                case 2:
                    lexemeList[lexemeCounter].tokenVal = procsym;
                    break;
                case 3:
                    lexemeList[lexemeCounter].tokenVal = callsym;
                    break;
                case 4:
                    lexemeList[lexemeCounter].tokenVal = beginsym;
                    break;
                case 5:
                    lexemeList[lexemeCounter].tokenVal = endsym;
                    break;
                case 6:
                    lexemeList[lexemeCounter].tokenVal = ifsym;
                    break;
                case 7:
                    lexemeList[lexemeCounter].tokenVal = thensym;
                    break;
                case 8:
                    lexemeList[lexemeCounter].tokenVal = elsesym;
                    break;
                case 9:
                    lexemeList[lexemeCounter].tokenVal = whilesym;
                    break;
                case 10:
                    lexemeList[lexemeCounter].tokenVal = dosym;
                    break;
                case 11:
                    lexemeList[lexemeCounter].tokenVal = readsym;
                    break;
                case 12:
                    lexemeList[lexemeCounter].tokenVal = writesym;
                    break;
                case 13:
                    lexemeList[lexemeCounter].tokenVal = oddsym;
                    break;
                default:
                    lexemeList[lexemeCounter].tokenVal = identsym;
                    strcpy(lexemeList[lexemeCounter].name, word);
                    break;
            }
            lexemeCounter++;
        }
        if(isdigit(c)){
            int digit = c - '0';
            int digLength = 0;
            c = fgetc(input);

            while(isdigit(c)){
                if(digLength > 4){
                    printf("\nERROR: Number too long");
                    break;
                }

                digit = 10 * digit + (c - '0');
                digLength++;
            }

            //throws error if the variable starts with a number
            if(isalpha(c)){
                printf("ERROR: Variable does not start with letter");
                while(isalpha(c)||isdigit(c)){
                    c = fgetc(input);
                }

                lexemeList[lexemeCounter].numVal = digit;
                lexemeList[lexemeCounter].tokenVal = numbersym;
            }
        }
        


    }
    


    
}