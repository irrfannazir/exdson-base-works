#include "../data.h"
#include "../include/declare.h"
#include "../include/buffer.h"
#include <stdio.h>
#include <string.h>


extern int line_method[MAX];
extern int line_size;

int declare_default_var(int index, int size){
    //single a
    //Any datatype can be called
    if(
        type[index] == t_datatype
            &&
        type[index+1] == t_identifier
            &&
        size == 2
    ){
        printf("The %s has declared with the name of %s.\n", token[index], token[index+1]);
        line_method[line_size] = 0;
        line_size++;
        return -1;
    }
    return 1;
}

int declare_default_array(int index, int size){
    //single a[]
    //Any datatype can be called
    if(
        type[index] == t_datatype
            &&
        type[index + 1] == t_identifier
            &&
        array_limit_specifier(index + 2, size - 2)
            &&
        strcmp(token[index + size -1], "]") == 0
    ){
        printf("The single array has been declared.\n");
        line_method[line_size] = 1;
        line_size++;
        return -1;
    }
    
    return 2;
}

