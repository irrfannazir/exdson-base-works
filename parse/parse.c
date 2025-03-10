#include "../data.h"
#include "include/tree_node.h"
#include "include/print.h"
#include "include/declare.h"
#include "include/declare_simple_var.h"
#include <stdio.h>


int root_index;
int found_the_syntax;
struct Node *root_array[500];



void switch_case(int index, int size){
    found_the_syntax = 0;
    root_index = 0;
    while(found_the_syntax == 0){
        switch(root_index){
            case 0:
                declare_the_variable(index, size);
                break;
            default:
                printe("Invalid syntax.", num_lines(index + 1), 0);
                found_the_syntax = 1;
                break;
        }
        root_index++;
    }
}

void parsef(){
    int i = 0;
    int j = 0;
    printf("Parsing the tokens.\n");
    while(i+j < token_size){
        if(type[i+j] == t_eof){
            switch_case(i, j);
            i = i+j+1;
            j = 0;
        }else{
            j++;
        }
    }
    
}
