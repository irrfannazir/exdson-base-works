#include "../data.h"
#include "./include/constants.h"
#include <stdio.h>

void printe(char *str, int line_index, int size){
    int lines = num_lines(line_index) + 1;
    printf("Error ( %d:%d ): ", lines, size);
    printf(str);
    if(dont_compile == 0){
        dont_compile = 1;
    }
    printf("\n");
}

void printw(char *str){
    printf("Warning: ");
    printf(str);
    printf("\n");
}