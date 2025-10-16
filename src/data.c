#include "../data.h"
#include <stdio.h>

char token[TOKEN_SIZE_MAX][TOKEN_STRING_MAX];
t_type type[TOKEN_SIZE_MAX];
int indent_token[TOKEN_SIZE_MAX];
int token_size;
int total_error;
int dont_compile = 0;


struct Node *root_array[500];


int line_method[LINE_MAX];
int line_size = 0;
int parametre_list[LINE_MAX][PARAMETRE_MAX];

int ismath = 0;

//To count number of lines
int num_lines(int size){
    if(size == -1){
        size = token_size;
    }
    int res = 0;
    for(int i = 0;i < size; i++){
        if(get_type(i) == TOKEN_EOF){
            res++;
        }
    }
    return res;
}

void display_token(){
    ;
}
