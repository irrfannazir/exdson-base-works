#include "data.h"
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
        if(type[i] == TOKEN_EOF){
            res++;
        }
    }
    return res;
}

void display_token(){
    for(int i = 0; i < token_size; i++){
        printf("%s\nThe type %d is ", token[i], i);
        switch(type[i]){
            case 0:
                printf("eof");
                break;
            case 1:
                printf("identifier");
                break;
            case 2:
                printf("integer");
                break;
            case 3:
                printf("tkeyword");
                break;
            case 4:
                printf("op");
                break;
            case 5:
                printf("punctuation");
                break;
            case 6:
                printf("datatype");
                break;
            case 7:
                printf("expression");
                break;
            case 8:
                printf("string");
                break;
        }
        printf("\n");
    }
    // printf("indentations pr line.\n");
    // for(int i = 0;i < num_lines(); i++){
        // printf("%d: %d\n", i, indent_token[i]);
    // }
    printf("The total errors is %d\n", total_error);
}
