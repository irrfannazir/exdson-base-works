#include <stdlib.h>
#include <stdio.h>
#include "compile/cfh.h"
#include "compile/compileh.h"
#include "parse/strh.h"
#include "common/fileh.h"
#include "data.h"

void process_parametres(const char *dfn, int *arr, int count){
    if (!arr || count <= 0) return;
    switch(arr[0]){
        case INSTRUCTION_DECLARATION:
        case INSTRUCTION_DECLARATION_WITHOUT_ASSIGNMENT:
            declaration_exec(dfn, arr, count);
            break;
        case INSTRUCTION_ASSIGNMENT:
            assign_exec(dfn, arr, count);
            break;
        case INSTRUCTION_IF_BLOCK:
            block_paradigm(dfn, "if", arr, count);
            break;
        case INSTRUCTION_ELSE_IF_BLOCK:
            block_paradigm(dfn, "else if", arr, count);    
            break;
        case INSTRUCTION_ELSE_BLOCK:
            else_condition(dfn);
            break;
        case INSTRUCTION_FOR_BLOCK:
            for_condition(dfn, arr, count);
            break;
        case INSTRUCTION_WHILE_BLOCK:
            block_paradigm(dfn, "while", arr, count);
            break;
        case INSTRUCTION_PRINT:
            print_statement(dfn, arr, count);
            break;
        case INSTRUCTION_FUNCTION:
            function_declaration(dfn, arr[1]);
            break;
        case INSTRUCTION_FUNCTION_WITH_ARGS:
            function_declaration_with_args(dfn, arr, count);
            break;
        default:
            fprintf(stderr, "Unknown instruction code: %d\n", arr[0]);
            break;
    }
}

static int instruction_opens_block(int instruction) {
    return instruction == INSTRUCTION_IF_BLOCK ||
           instruction == INSTRUCTION_ELSE_IF_BLOCK ||
           instruction == INSTRUCTION_ELSE_BLOCK ||
           instruction == INSTRUCTION_FOR_BLOCK ||
           instruction == INSTRUCTION_WHILE_BLOCK ||
           instruction == INSTRUCTION_FUNCTION ||
           instruction == INSTRUCTION_FUNCTION_WITH_ARGS;
}

static void close_generated_block(const char *dfn) {
    remove_string_from_file(dfn, PGM_CURSOR, 0);
    fputs_with_newl(PARSED_INFORMATION, "end of the finally mentioned block");
}

void add_the_program(const char *pfn, const char *dfn){
    int i = 0;
    char *parsed_data = get_nth_line(pfn, i, NULL);

    int current_indent = 0;
    int tab_space_count = -1;
    int current_depth = 0;

    while(parsed_data != NULL){
        trim_newline(parsed_data);

        int next_indent = get_indentation(i);
        if (tab_space_count == -1 && next_indent > 0) {
            tab_space_count = next_indent;
        }

        if (tab_space_count > 0) {
            while (current_indent > next_indent && current_depth > 0) {
                close_generated_block(dfn);
                current_depth--;
                current_indent -= tab_space_count;
            }
        }

        int count;
        int *arr = line_to_int_array(parsed_data, &count);
        int opens_block = arr && count > 0 && instruction_opens_block(arr[0]);
        
        process_parametres(dfn, arr, count);
        free(parsed_data);

        if (opens_block) {
            int following_indent = get_indentation(i + 1);
            if (tab_space_count == -1 && following_indent > next_indent) {
                tab_space_count = following_indent - next_indent;
            }

            if (tab_space_count > 0 && following_indent > next_indent) {
                current_depth++;
                current_indent = following_indent;
            }
        }
        
        free(arr);

        i++;
        parsed_data = get_nth_line(pfn, i, NULL);
    }

    while (current_depth > 0) {
        close_generated_block(dfn);
        current_depth--;
    }
}

int compilef(const char *src_filename, const char *dest_filename){
    if(dont_compile) return 1;
    printf("Compiling the program.\n");
    if (create_file(dest_filename, DEFAULT_PROGRAM)) return 1;
    if (create_file(PARSED_INFORMATION, "")) return 1;
    add_the_program(src_filename, dest_filename);
    printf("********The output program implemented in C programming Language********\n\n");
    remove_string_from_file(dest_filename, PGM_CURSOR, 1);
    remove_string_from_file(dest_filename, FUNCTION_CURSOR, 1);
    remove_string_from_file(dest_filename, INCLUDE_CURSOR, 1);
    print_file_content(dest_filename);
    printf("\n\n\n");
    return compile_file(dest_filename);
}
