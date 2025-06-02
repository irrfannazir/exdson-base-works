#include "../data.h"
#include "include/constants.h"
#include "include/expression.h"
#include <stdio.h>
#include <string.h>

void if_condition(int index, int size){
    if(
        strcmp(token[index], "if") == 0
            &&
        strcmp(token[index + 1], "(") == 0
            &&
        expression(index + 2, size - 4)
            &&
        strcmp(token[index + size - 2], ")") == 0
            &&
        strcmp(token[index + size - 1], ":") == 0
    ){
        int current_line = num_lines(index);
        if(indent_token[current_line] + 1 != indent_token[current_line + 1]){
            printf("Error (%d:0): Indentation Error.\n", current_line);
            found_the_syntax = 1;
            dont_compile = 1;
            return;
        }
        parametre_list[line_size][0] = index + 2;
        parametre_list[line_size][1] = index + size - 2;
        parametre_list[line_size][2] = -1;
        line_method[line_size] = 2;
        line_size++;
        found_the_syntax = 1;
    }
}

void else_condition(int index, int size){
    if(
        strcmp(token[index], "else") == 0
        &&
        strcmp(token[index + 1], ":") == 0
    ){
        int current_line = num_lines(index);
        if(indent_token[current_line] + 1 != indent_token[current_line + 1]){
            printf("Error (%d:0): Indentation Error.\n", current_line);
            found_the_syntax = 1;
            dont_compile = 1;
            return;
        }
        parametre_list[line_size][0] = -1;
        line_method[line_size] = 3;
        line_size++;
        found_the_syntax = 1;
    }
}