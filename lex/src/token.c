#include "token.h"
#include "..\data.h"
#include <stdio.h>

//from token.h
extern int is_eof;
extern int token_len;
extern int isstring;


//datatypes
t_type temp = t_eof;


//Append the character to the token
void append(char c){
    token[token_size][token_len] = c;
    token_len++;
}

//Move the cursor to new token
void new_token(char c){
    //Checks whether end of file is repeating
    if(!is_eof || temp != t_eof){
        token[token_size][token_len] = '\0';
        type[token_size] = temp;
        //Put a flag whether a end of file is appended
        if(temp == t_eof){
            is_eof = 1;
        }else{
            is_eof = 0;
        }
        // Checks whether the token is not empty
        if(token_len != 0){
            token_len = 0;
            token_size++;
        }else if(type[token_size] == t_eof){
            token_len = 0;
            token_size++;
        }
        if(c != '\0'){
            //Check whether the c is not a null
            token[token_size][token_len] = c;
            temp = t_eof;
            token_len = 1;
        }
    }else if(c != '\0'){
        //Check whether the c is not a null
        token[token_size][token_len] = c;
        temp = t_eof;
        token_len = 1;
        is_eof = 0;
    }
}


void error_found(){
    total_error++;
}

int last_in(){
    return type[token_size - 1];
}

void next_type(int next){
    temp = next;
}

int prev_type(){
    return temp;
}

int size(){
    return token_size;
}




int num_lines(int size);
void display_token();