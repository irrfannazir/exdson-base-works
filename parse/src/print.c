#include "../data.h"
#include "./include/constants.h"
#include <stdio.h>

void printe(char *str, int line_index, int size){
    int lines = num_lines(line_index) + 1;
    printf("Error ( %d:%d ): ", lines, size);
    printf("%s", str);
    if(dont_compile == 0){
        dont_compile = 1;
    }
    printf("\n");
}

void printw(char *str){
    printf("Warning: ");
    printf("%s", str);
    printf("\n");
}