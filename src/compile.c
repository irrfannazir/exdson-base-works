#include <stdlib.h>
#include <stdio.h>
#include "compile/cfh.h"
#include "compile/compileh.h"
#include "parse/strh.h"
#include "common/fileh.h"
#include "data.h"

void process_parametres(const char *dfn, int *arr, int count){
    switch(arr[0]){
        case 0:
            declaration_exec(dfn, arr, count);
            break;
        case 2:
            block_paradigm(dfn, "if", arr, count);
            break;
        case 3:
            block_paradigm(dfn, "else if", arr, count);    
            break;
        case 4:
            else_condition(dfn, arr, count);
            break;
        case 5:
            for_condition(dfn, arr, count);
            break;
        case 6:
            block_paradigm(dfn, "while", arr, count);
            break;
        case 7:
            print_statement(dfn, arr, count);
            break;
    }
}

void add_the_program(const char *pfn, const char *dfn){
    int i = 0;
    char *parsed_data = get_nth_line(pfn, i, NULL);
    int indent_tab_number = 0;
    i++;
    while(parsed_data != NULL){
        trim_newline(parsed_data);
        if(get_indentation(i - 2) < get_indentation(i - 1)){
            if(indent_tab_number == 0){
                indent_tab_number = get_indentation(i - 1) - get_indentation(i - 2);
            }
        }
        int count;
        int *arr = line_to_int_array(parsed_data, &count);
        process_parametres(dfn, arr, count);
        parsed_data = get_nth_line(PARSING_HANDLING_FILE_NAME, i, NULL);
        i++;
        if( ( get_indentation(i - 3) - indent_tab_number == get_indentation(i - 2) ) && indent_tab_number != 0){
            remove_string_from_file(dfn, PGM_CURSOR, 0);
        }
        free(arr);
    }
}

int compilef(const char *src_filename, const char *dest_filename){
    if(dont_compile) return 1;
    printf("Compiling the program.\n");
    create_file(dest_filename, DEFAULT_PROGRAM);
    add_the_program(src_filename, dest_filename);
    printf("********The output program implemented in C programming Language********\n\n");
    remove_string_from_file(dest_filename, PGM_CURSOR, 1);
    remove_string_from_file(dest_filename, FUNCTION_CURSOR, 1);
    remove_string_from_file(dest_filename, INCLUDE_CURSOR, 1);
    print_file_content(dest_filename);
    printf("\n\n\n");
    compile_file(dest_filename);
    return 0;
}
