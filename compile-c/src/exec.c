#include "../data.h"
#include "../parse/include/tree_node.h"
#include "../include/str.h"
#include "../include/execution.h"
#include "../include/basic.h"
#include "../fileh.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int pgm_cursor = 11;
int parametre_index;


int find_next_block(int start, int iter){
    char *pgm = read_file(PGM_EXATED_FILE_NAME);
    for(int i = start; pgm[i] != '\0'; i++){
        if(pgm[i] == '}'){
            iter--;
        }
        if(iter == 0){
            return i + 1;
        }
    }
}


void add_the_program(){
    int include_cursor = 0;
    int function_cursor = 0;
    int datatype;
    for(parametre_index = 0; parametre_index < line_size; parametre_index++){
        if(indent_token[parametre_index - 1] - 1 == indent_token[parametre_index]){
            pgm_cursor = find_next_block(pgm_cursor, 1);
        }
        switch(line_method[parametre_index]){
            case 0:
                declaration_execution();
                break;
            case 1:
                print_execution_with_array(&include_cursor);
                break;
            case 2:
                if_execution();
                break;
            case 3:
                else_execution();
                break;
            case 4:
                // for elif condition
                break;
        }
    }
    (ismath) ? (append_library(PGM_EXATED_FILE_NAME, "<math.h>", include_cursor)):(0);
    printf("\n");
    return;
}
