#include "token.h"
#include "../data.h"
#include <stdio.h>
#include <stdlib.h>

//from token.h
extern int is_eof;
extern int token_len;
extern int isstring;


//The temporary type
t_type temp = TOKEN_EOF;

int a = 0;

//Append the character to the token
void append(char c){
    token[token_size][token_len] = c;
    token_len++;
    if(token_len >= TOKEN_SIZE_MAX){
        printf("The TOKEN_SIZE_MAXin (data.h) is less than you need.\n");
        exit(0);
    }
}

//Move the cursor to new token
void new_token(char c){
    //Checks whether end of file is repeating
    if(!is_eof || temp != TOKEN_EOF){
        token[token_size][token_len] = '\0';
        type[token_size] = temp;
        //Put a flag whether a end of file is appended
        if(temp == TOKEN_EOF){
            is_eof = 1;
        }else{
            is_eof = 0;
        }
        // Checks whether the token is not empty
        if(token_len != 0){
            token_len = 0;
            token_size++;
        }else if(type[token_size] == TOKEN_EOF){
            token_len = 0;
            token_size++;
        }
        if(c != '\0'){
            //Check whether the c is not a null
            token[token_size][token_len] = c;
            temp = TOKEN_EOF;
            token_len = 1;
        }
    }else if(c != '\0'){
        //Check whether the c is not a null
        token[token_size][token_len] = c;
        temp = TOKEN_EOF;
        token_len = 1;
        is_eof = 0;
    }
    if(token_size >= TOKEN_STRING_MAX){
        // printf("");
    }
}

void next_type(int next){
    temp = next;
}

int prev_type(){
    return temp;
}
