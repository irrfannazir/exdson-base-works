#include <stdlib.h>
#include <stdio.h>
#include "../data.h"
#include "include/compileh.h"


void process_parametres(int *arr, int count){
    switch(arr[0]){
        case 0:
            declaration_exec(arr, count);
            break;
        case 2:
            block_paradigm("if", arr, count);
            break;
        case 3:
            block_paradigm("else if", arr, count);    
            break;
        case 4:
            else_condition(arr, count);
            break;
        case 5:
            for_condition(arr, count);
            break;
        case 6:
            block_paradigm("while", arr, count);
            break;
        case 7:
            print_statement(arr, count);
            break;
    }
}

void add_the_program(){
    int i = 1;
    char *parsed_data = get_nth_line_from_parse(i);
    int indent_tab_number = 0;
    i++;
    while(parsed_data != NULL){
        if(get_indentation(i - 2) < get_indentation(i - 1)){
            if(indent_tab_number == 0){
                indent_tab_number = get_indentation(i - 1) - get_indentation(i - 2);
            }
        }
        int count;
        int *arr = line_to_int_array(parsed_data, &count);
        process_parametres(arr, count);
        parsed_data = get_nth_line_from_parse(i);
        i++;
        if( ( get_indentation(i - 3) - indent_tab_number == get_indentation(i - 2) ) && indent_tab_number != 0){
            remove_string_from_file(PGM_EXATED_FILE_NAME, PGM_CURSOR, 0);
        }
    }
}

int compilef(){
    if(dont_compile) return 1;
    printf("Compiling the program.\n");
    create_file(PGM_EXATED_FILE_NAME, DEFAULT_PROGRAM);
    add_the_program();
    printf("********The output program implemented in C programming Language********\n\n");
    remove_string_from_file(PGM_EXATED_FILE_NAME, PGM_CURSOR, 1);
    remove_string_from_file(PGM_EXATED_FILE_NAME, FUNCTION_CURSOR, 1);
    remove_string_from_file(PGM_EXATED_FILE_NAME, INCLUDE_CURSOR, 1);
    print_file(PGM_EXATED_FILE_NAME);
    printf("\n\n\n");
    compile_file(PGM_EXATED_FILE_NAME);
    return 0;
}