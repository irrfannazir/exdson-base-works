#include "data.h"
#include "parse/include/tree_node.h"
#include <stdio.h>

char token[MAX][MAX];
t_type type[MAX];
int token_size;
int total_error;
int indent_token[MAX];
int dont_compile = 0;

struct Node *root_array[500];


int line_method[MAX];
int line_size = 0;
int parametre_list[MAX][MAX];

//To count number of lines
int num_lines(int size){
    if(size == -1){
        size = token_size;
    }
    int res = 0;
    for(int i = 0;i < size; i++){
        if(type[i] == t_eof){
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
