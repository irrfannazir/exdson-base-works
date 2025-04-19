#include "expression.h"
#include "../data.h"
#include <string.h>

int is_unary_operator(char *operator){
    for(int i = 0; operator[i] != '\0'; i++){
        if(
            strcmp(operator, "!") != 0 
                &&
            strcmp(operator, "~") != 0
        ){
            return 0;
        }
    }
    return 1;
}

int find_the_unary(int index, int size){
    if(
        is_unary_operator(token[index])
            &&
        size == 2
    ){
        return 1;
    }else if(
        is_unary_operator(token[index])
            &&
        strcmp(token[index + 1], "(") == 0
            &&
        strcmp(token[index + size - 1], ")") == 0
    ){
        return 2;
    }
    return -1;
}

