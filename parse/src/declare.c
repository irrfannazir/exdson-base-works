#include "../data.h"
#include "./include/buffer.h"
#include "./include/print.h"
#include "./include/debug.h"
#include "./include/declare.h"
#include "./include/constants.h"
#include <string.h>
#include <stdio.h>

// extern int line_method[MAX];
// extern int line_size;


void declare_the_variable(int index, int size){
    //single a = <?expression?>
    
    if(
        type[index] == t_datatype
        // strcmp(token[index], "single") == 0
            &&
        type[index+1] == t_identifier
            &&
        strcmp(token[index+2], "=") == 0
            &&
        size > 3
            &&
        expression(index+3, size - 3)
    ){
        printf("The %s has declared with the name %s and assigned an expression.\n", token[index], token[index+1]);
        parametre_list[line_size][0] = index;
        parametre_list[line_size][1] = index+1;
        parametre_list[line_size][2] = index+3;
        parametre_list[line_size][3] = index+size;
        parametre_list[line_size][4] = -1;
        line_method[line_size] = 0;
        line_size++;
        found_the_syntax = 1;
    }
}
