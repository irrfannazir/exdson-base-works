#include "../data.h"
#include "include/print.h"
#include <stdio.h>

//The Syntax Checking Libraries
#include "parseh.h"


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
            case 1:
                print_the_string(index, size);
                break;
            case 2:
                if_condition(index, size);
                break;
            case 3:
                else_condition(index, size);
                break;
            default:
                printe("Invalid syntax.", index, 0);
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
        if(type[i+j] == TOKEN_EOF){
            switch_case(i, j);
            i = i+j+1;
            j = 0;
        }else{
            j++;
        }
    }
}
