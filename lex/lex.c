#include "include/indent.h"
#include "include/token.h"
#include "include/character.h"
#include "include/keyword.h"
#include "include/fileh.h"
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




void lexf(){
    char *com;
    int cursor = 0;
    int i = 0;
    int j;
    char delimiter = ';';    
    int iscolonfound = 0;
    int isspace = 0;
    int isenter = 0;
    int iscurly = 0;
    int space_count = 0;

    #ifdef READ_FROM_INPUT
        com = (char*)malloc(500);
        scanf("%[^#]s", com);
        #undef READ_FROM_INPUT
    #else
        com = read_file_into_buffer(READING_FILE_DIRECTORY);
        printf("%s\n", com);
        #undef READING_FILE_DIRECTORY
    #endif
    
    printf("\nTokenizing the command.\n");
    while(com[i] != '\0'){
        // Analyze each characters
        if(isstring){
            //Append if it is a string
            if(com[i] == '\"'){
                isstring = 0;
            }else{
                append(com[i]);
            }
        }
        else if(com[i] == ' '){
            //The space is ignored.
            //The indent should be count for the execution
            if(isspace == 0 && isenter == 0){
                new_token('\0');
            }
            if(iscolonfound && isenter){
                add_indent(&space_count);
                isenter = 1;
            }else{
                isenter = 0;
            }
            isspace = 1;
        }
        else if(com[i] == '\n' || com[i] == delimiter){
            if(iscurly){
                i++;
                continue;
            }
            //The delimiter is encountered.
            new_token('\0');
            isspace = 0;
            next_type(TOKEN_EOF);
            new_token('\0');
            isenter = 1;
        }
        else if(is_char(com[i])){
            //The character is encountered.
            isspace = 0;
            if(prev == CTYPE_CHAR || prev == CTYPE_DIGIT){
                append(com[i]);
            }else if(prev == CTYPE_OPERATOR || prev == CTYPE_PUNCT){
                new_token(com[i]);
            }
            isenter = 0;
            next_type(TOKEN_IDENTIFIER);
            prev = CTYPE_CHAR;
            clear_indent(&iscolonfound);
        }else if(is_digit(com[i])){
            // The digit is encountered.
            isspace = 0;
            if(prev == CTYPE_CHAR || prev == CTYPE_DIGIT){
                //When the digit is found after the dot.
                append(com[i]);
            }else if(prev == CTYPE_OPERATOR || prev == CTYPE_PUNCT){
                new_token(com[i]);
            }
            if(prev_type() != TOKEN_IDENTIFIER){
                next_type(TOKEN_INTEGER);
            }
            isenter = 0;
            prev = CTYPE_DIGIT;
            clear_indent(&iscolonfound);
        }else if(is_oper(com[i])){
            // The operator is encountered.
            if(prev == CTYPE_OPERATOR){
                append(com[i]);
            }else if(prev == CTYPE_CHAR || prev == CTYPE_PUNCT || prev == CTYPE_DIGIT){
                new_token(com[i]);
            }
            isenter = 0;
            prev = CTYPE_OPERATOR;
            next_type(TOKEN_OPERATOR);
            isspace = 0;
            clear_indent(&iscolonfound);
        }else if(com[i] == '{'){
            new_token(com[i]);
            next_type(TOKEN_PUNCTUATION);
            prev = CTYPE_PUNCT;
            isenter = 0;
            isspace = 0;
            iscurly = 1;
        }else if(com[i] == '}'){
            new_token(com[i]);
            next_type(TOKEN_PUNCTUATION);
            prev = CTYPE_PUNCT;
            isspace = 0;
            iscurly = 0;
            isenter = 0;
        }else if(com[i] == '\"'){
            // if(isstring){
                new_token('\0');
            // }else{
                // append(com[i]);
            // }
            next_type(TOKEN_STRING);
            prev = CTYPE_PUNCT;
            isstring = !isstring;
        }else if(com[i] == '.'){
            if(prev == CTYPE_DIGIT){
                append('.');
            }else{
                new_token('.');
                prev = CTYPE_PUNCT;
                next_type(TOKEN_PUNCTUATION);
            }
            isspace = 0;
        }else if(is_punct(com[i])){
            //The punctuator is encountered.
            new_token(com[i]);
            if(com[i] == ':'){
                iscolonfound++;
            }else{
                clear_indent(&iscolonfound);
            }
            isenter = 0;
            next_type(TOKEN_PUNCTUATION);
            prev = CTYPE_PUNCT;
            isspace = 0;
        }else{
            isspace = 0;
            new_token(com[i]);
            next_type(TOKEN_PUNCTUATION);
            printf("Error: The unknown character '%c' is found at line %d: %d\n", com[i], num_lines(-1), i);
            error_found();
            clear_indent(&iscolonfound);
            isenter = 0;
        }
        i++;
    }
    
    if(com[i] != ' ' | com[i] != '\n' | com[i] != delimiter){
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