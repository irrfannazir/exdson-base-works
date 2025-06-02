#include "include/lexh.h"
#include "include/debug.h"
#include "../fileh.h"
#include "../dependencies.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//The c_type is to store the type of previous character
typedef enum{
    CTYPE_CHAR, // character value (a-z, A-Z)
    CTYPE_DIGIT, // digit value (0-9)
    CTYPE_PUNCT, // punctuators
    CTYPE_OPERATOR // operator
} c_type;


typedef enum{
    TOKEN_EOF,          // 0 End Of File
    TOKEN_IDENTIFIER,   // 1 Identifiers (variables, function names, etc.)
    TOKEN_INTEGER,      // 2 Integer literals (e.g., 123, 456)
    TOKEN_KEYWORD,      // 3 Keywords (e.g., if, for, while, etc.)
    TOKEN_OPERATOR,     // 4 Operators (e.g., +, -, *, /, ==)
    TOKEN_PUNCTUATION,  // 5 Punctuation (e.g., (, ), {, }, ;, ,)
    TOKEN_DATATYPE,     // 6 Datatypes (e.g., int, float, char)
    TOKEN_EXPRESSION,   // 7 Expressions (e.g., arithmetic, logical)
    TOKEN_STRING        // 8 String literals (e.g., "Hello")
} t_type;


//The Global variables
int token_len = 0;
int is_eof = 0;
int isstring = 0;

c_type prev;

//For character analysis
int isenter = 0;
int isspacef = 0;
int iscurly = 0;
const char delimiter = ';';    
int iscolonfound = 0;
int space_count = 0;

int char_analysis(char c){
    // Analyze each characters
    if(isstring){
        //Append if it is a string
        if(c == '\"'){
            isstring = 0;
        }else{
            append(c);
        }
    }
    else if(c == ' '){
        //The space is ignored.
        //The indent should be count for the execution
        if(isspacef == 0 && isenter == 0){
            new_token('\0');
        }
        if(iscolonfound && isenter){
            add_indent(&space_count);
            isenter = 1;
        }else{
            isenter = 0;
        }
        isspacef = 1;
    }
    else if(c == '\n' || c == delimiter){
        if(iscurly != 0){
            return 0;
        }
        //The delimiter is encountered.
        new_token('\0');
        isspacef = 0;
        next_type(TOKEN_EOF);
        new_token('\0');
        isenter = 1;
    }
    else if(is_char(c)){
        //The character is encountered.
        isspacef = 0;
        if(prev == CTYPE_CHAR || prev == CTYPE_DIGIT){
            append(c);
        }else if(prev == CTYPE_OPERATOR || prev == CTYPE_PUNCT){
            new_token(c);
        }
        isenter = 0;
        next_type(TOKEN_IDENTIFIER);
        prev = CTYPE_CHAR;
        clear_indent(&iscolonfound);
    }else if(is_digit(c)){
        // The digit is encountered.
        isspacef = 0;
        if(prev == CTYPE_CHAR || prev == CTYPE_DIGIT){
            //When the digit is found after the dot.
            append(c);
        }else if(prev == CTYPE_OPERATOR || prev == CTYPE_PUNCT){
            new_token(c);
        }
        if(prev_type() != TOKEN_IDENTIFIER){
            next_type(TOKEN_INTEGER);
        }
        isenter = 0;
        prev = CTYPE_DIGIT;
        clear_indent(&iscolonfound);
    }else if(is_oper(c)){
        // The operator is encountered.
        if(prev == CTYPE_OPERATOR){
            append(c);
        }else if(prev == CTYPE_CHAR || prev == CTYPE_PUNCT || prev == CTYPE_DIGIT){
            new_token(c);
        }
        isenter = 0;
        prev = CTYPE_OPERATOR;
        next_type(TOKEN_OPERATOR);
        isspacef = 0;
        clear_indent(&iscolonfound);
    }else if(c == '{' || c == '('){
        new_token(c);
        next_type(TOKEN_PUNCTUATION);
        prev = CTYPE_PUNCT;
        isenter = 0;
        isspacef = 0;
        iscurly++;
    }else if(c == '}' || c == ')'){
        new_token(c);
        next_type(TOKEN_PUNCTUATION);
        prev = CTYPE_PUNCT;
        isspacef = 0;
        isenter = 0;
        iscurly--;
    }else if(c == '\"'){
        // if(isstring){
            new_token('\0');
        // }else{
            // append(c);
        // }
        next_type(TOKEN_STRING);
        prev = CTYPE_PUNCT;
        isstring = !isstring;
    }else if(c == '.'){
        if(prev == CTYPE_DIGIT){
            append('.');
        }else{
            new_token('.');
            prev = CTYPE_PUNCT;
            next_type(TOKEN_PUNCTUATION);
        }
        isspacef = 0;
    }else if(is_punct(c)){
        //The punctuator is encountered.
        new_token(c);
        if(c == ':'){
            iscolonfound++;
        }else{
            clear_indent(&iscolonfound);
        }
        isenter = 0;
        next_type(TOKEN_PUNCTUATION);
        prev = CTYPE_PUNCT;
        isspacef = 0;
    }else{
        isspacef = 0;
        new_token(c);
        next_type(TOKEN_PUNCTUATION);
        printf("Error: The unknown character '%c' is found.\n", c);
        error_found();
        clear_indent(&iscolonfound);
        isenter = 0;
    }
    return 0;
}


void lexf(){
    char c;
    int cursor = 0;
    int j;
    
    #ifdef READ_FROM_INPUT
        char *com;
        int i = 0;
        com = (char*)malloc(PGM_MAX);
        scanf("%[^#]s", com);
        while(com[i] != '\0'){
            char_analysis(com[i]);
            i++;
        }
        c = com[i];
        #undef READ_FROM_INPUT
    #else
        // com = read_file(READING_FILE_DIRECTORY);
        // printf("%s\n", com);
        FILE *file = fopen(READING_FILE_DIRECTORY, "r");
        while((c = fgetc(file)) != EOF){
            char_analysis(c);
        }
        #undef READING_FILE_DIRECTORY
    #endif
    
    printf("\nTokenizing the command.\n");


    if(c != ' ' && c != '\n' && c != delimiter){
        new_token('\0');
    }
    if(last_in() != TOKEN_EOF){
        next_type(TOKEN_EOF);
        new_token('\0');
    }
    filter_keyword();

    #ifdef DISPLAY_TOKEN
      display_token();
    #endif
    #undef DISPLAY_TOKEN
    return ;
}