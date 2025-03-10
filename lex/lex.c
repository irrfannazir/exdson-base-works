#include "include/indent.h"
#include "include/token.h"
#include "include/character.h"
#include "include/keyword.h"
// #include "..\data.h"
#include <stdio.h>
#include <string.h>
#define MAX 500


//The c_type is to store the type of previous character
typedef enum{
    c_char, c_digit, c_punct, c_operator
} c_type;


typedef enum{
    t_eof, t_identifier, t_integer, t_keyword,
    //0     1               2           3
    t_op, t_punctuation, t_datatype, t_expression, t_string
    //4     5               6           7           8
} t_type;


//The Global variables
int token_len = 0;
int is_eof = 0;
int isstring = 0;

c_type prev;


void lexf(){
    char com[MAX];
    int cursor = 0;
    int i = 0;
    int j;
    char delimiter = ';';    
    int iscolonfound = 0;
    int isspace = 0;
    int isenter = 0;
    int iscurly = 0;
    int space_count = 0;
    scanf("%[^#]s", com);
    printf("Tokenizing the command.\n");
    while(com[i] != '\0'){
        // Analyze each characters
        if(isstring){
            //Append if it is a string
            append(com[i]);
        }
        else if(com[i] == ' '){
            //The space is ignored.
            //The indent should be count for the execution
            add_indent(&iscolonfound, &space_count);
            if(isspace == 0 && isenter == 0){
                new_token('\0');
            }
            isenter = 0;
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
            next_type(t_eof);
            new_token('\0');
            isenter = 1;
        }
        else if(is_char(com[i])){
            //The character is encountered.
            isspace = 0;
            if(prev == c_char || prev == c_digit){
                append(com[i]);
            }else if(prev == c_operator || prev == c_punct){
                new_token(com[i]);
            }
            isenter = 0;
            next_type(t_identifier);
            prev = c_char;
            clear_indent(&iscolonfound);
        }else if(is_digit(com[i])){
            // The digit is encountered.
            isspace = 0;
            if(prev == c_char || prev == c_digit){
                //When the digit is found after the dot.
                append(com[i]);
            }else if(prev == c_operator || prev == c_punct){
                new_token(com[i]);
            }
            if(prev_type() != t_identifier){
                next_type(t_integer);
            }
            isenter = 0;
            prev = c_digit;
            clear_indent(&iscolonfound);
        }else if(is_oper(com[i])){
            // The operator is encountered.
            if(prev == c_operator){
                append(com[i]);
            }else if(prev == c_char || prev == c_punct || prev == c_digit){
                new_token(com[i]);
            }
            isenter = 0;
            prev = c_operator;
            next_type(t_op);
            isspace = 0;
            clear_indent(&iscolonfound);
        }else if(com[i] == '{'){
            new_token(com[i]);
            next_type(t_punctuation);
            prev = c_punct;
            isenter = 0;
            isspace = 0;
            iscurly = 1;
        }else if(com[i] == '}'){
            new_token(com[i]);
            next_type(t_punctuation);
            prev = c_punct;
            isspace = 0;
            iscurly = 0;
            isenter = 0;
        }else if(com[i] == '\"'){
            if(isstring){
                new_token(com[i]);
            }else{
                append(com[i]);
            }
            next_type(t_string);
            prev = c_punct;
            isstring = !isstring;
        }else if(com[i] == '.'){
            if(prev == c_digit){
                append('.');
            }else{
                new_token('.');
                prev = c_punct;
                next_type(t_punctuation);
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
            next_type(t_punctuation);
            prev = c_punct;
            isspace = 0;
        }else{
            isspace = 0;
            new_token(com[i]);
            next_type(t_punctuation);
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
    if(last_in() != t_eof){
        next_type(t_eof);
        new_token('\0');
    }
    filter_keyword();
    // display_token();
    return ;
}