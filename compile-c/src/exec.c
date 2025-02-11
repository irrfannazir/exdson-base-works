#include "../data.h"
#include "../parse/include/tree_node.h"
#include "../include/str.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char *declaration_string(int identifier, int expression_start, int expression_end){
    char *new_pgm = (char *)malloc(MAX * sizeof(char));
                    // printf("%s.\n", new_pgm);
    strcpy(new_pgm, "");
    strcat(new_pgm, "int ");
                    // printf("%s.\n", new_pgm);
    strcat(new_pgm, token[identifier]);
    strcat(new_pgm, " = ");
    for(int i = expression_start; i < expression_end; i++){
        strcat(new_pgm, token[i]);
    }
                    // printf("%s.\n", new_pgm);
    strcat(new_pgm, ";");
                    // printf("%s.\n", new_pgm);
    return new_pgm;
}

void add_the_program(){
    int pgm_cursor = 11;
    int include_cursor = 0;
    int function_cursor = 0;
    int datatype;
    strcpy(pgm, "int main(){return 0;}");
    for(int i = 0; i < line_size; i++){
        switch(line_method[i]){
            case 0:
                datatype = parametre_list[i][0];
                if(strcmp(token[datatype], "single") == 0){
                    // printf("%s.\n", pgm);
                    pgm = append_at_index(pgm, declaration_string(parametre_list[i][1], parametre_list[i][2], parametre_list[i][3]), pgm_cursor);
                }
                break;
        }
        // printf("%d\n", line_method[i]);
        // display_postfix(root_array[i]);
    }
    printf("\n");
    return;
}