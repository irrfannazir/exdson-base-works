#include "../data.h"
#include "../include/str.h"
#include "../include/execution.h"
#include "../include/basic.h"
#include "../fileh.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int program_cursor[CURSOR_MAX];
int cursor_size = 2;
int parametre_index;


void add_the_program(){
    int datatype;
    program_cursor[FUNCTION_CURSOR] = 0;
    program_cursor[CURRENT_CURSOR] = 11;
    for(parametre_index = 0; parametre_index < line_size; parametre_index++){
        remove_cursor(indent_token[parametre_index - 1] - indent_token[parametre_index]);
        switch(line_method[parametre_index]){
            case 0:
                declaration_execution();
                break;
            case 1:
                print_execution_with_array();
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
    (ismath) ? (append_library(PGM_EXATED_FILE_NAME, "<math.h>", program_cursor[FUNCTION_CURSOR])):(0);
    printf("\n");
    return;
}
