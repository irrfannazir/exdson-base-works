#include "include/exio.h"
#include "../data.h"
#include "include/constants.h"
#include "include/buffer.h"
#include <stdio.h>
#include <string.h>

void print_the_string(int index, int size){
    printf("%d %s %s\n", 
        strcmp(token[index], "print") == 0
            ,
        token[index+1]
            ,
        token[index+size-1]
    );
    const char delimiter = ',';
    if(
        strcmp(token[index], "print") == 0
            &&
        strcmp(token[index+1], "{") == 0
            &&
        strcmp(token[index+size-1], "}") == 0
            &&
        split_with_delimiter(index + 2, index - size - 1, delimiter)
    ){
        
        printf("The print function: ");
        int i = 0;
        for(int j = index+2; j < index + size - 1; j++){
            if(token[j][0] != delimiter){
                parametre_list[line_size][i] = j;
                i++;
            }
        }
        parametre_list[line_size][i] = -1;
        line_method[line_size] = 1;
        line_size++;
        found_the_syntax = 1;
        printf("\n");
    }
}
