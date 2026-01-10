#include "../data.h"
#include "../include/fileh.h"
#include "lexh.h"
#include <stdio.h>
#include <stdlib.h>
#include "token_check.h"

//from lexh.h
extern int is_eof;
extern int isstring;


//The temporary type
t_type temp = TOKEN_EOF;
char current_token[TOKEN_STRING_MAX];

int a = 0;

//Append the character to the token
void append(char c, int *current_token_length){
    current_token[*current_token_length] = c;
    (*current_token_length)++;
    if(*current_token_length >= TOKEN_SIZE_MAX){
        printf("The TOKEN_SIZE_MAX in (data.h) is less than you need.\n");
        exit(0);
    }
}

//Move the cursor to new token
void new_token(char c, int *current_token_length){
    //Checks whether end of file is repeating
    if(!is_eof || temp != TOKEN_EOF){
        type[token_size] = temp;
        current_token[*current_token_length] = '\0';
        //Put a flag whether a end of file is appended
        if(temp == TOKEN_EOF){
            is_eof = 1;
        }else{
            is_eof = 0;
        }
        // Checks whether the token is not empty
        if(*current_token_length != 0){
            check_datatype(current_token, &type[token_size]);
            append_token_to_file(LEX_HANDLING_FILE_NAME, type[token_size], current_token);
            *current_token_length = 0;
            token_size++;
        }else if(type[token_size] == TOKEN_EOF){
            check_datatype(current_token, &type[token_size]);
            append_token_to_file(LEX_HANDLING_FILE_NAME, type[token_size], current_token);
            *current_token_length = 0;
            token_size++;
        }
        if(c != '\0'){
            //Check whether the c is not a null
            current_token[*current_token_length] = c;
            temp = TOKEN_EOF;
            *current_token_length = 1;
        }
    }else if(c != '\0'){
        //Check whether the c is not a null
        current_token[*current_token_length] = c;
        temp = TOKEN_EOF;
        *current_token_length = 1;
        is_eof = 0;
    }
}

void next_type(int next){
    temp = next;
}

int prev_type(){
    return temp;
}
