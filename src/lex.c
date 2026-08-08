#include "lex/lexh.h"
#include "lex/lexInfo.h"
#include "lex/d_fh.h"
#include "lex/lerror.h"
#include "lex/dfaf.h"
#include "common/pc_error.h"
#include "common/fileh.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "parse/pdebug.h"


int dont_compile = 0;
#ifdef LINE_ANALYSIS
char src_filename[LINE_FILENAME_MAX];
#endif

static char *read_inline_program(void) {
    size_t capacity = INLINE_PROGRAM_MAX_SIZE;
    size_t length = 0;
    char *program = malloc(capacity);
    if (!program) {
        __pc_error__("The memory allocation failed while reading input");
        return NULL;
    }

    int ch;
    while ((ch = getchar()) != EOF && ch != '#') {
        if (length + 1 >= capacity) {
            size_t next_capacity = capacity * 2;
            char *resized = realloc(program, next_capacity);
            if (!resized) {
                free(program);
                __pc_error__("The memory allocation failed while expanding input");
                return NULL;
            }
            program = resized;
            capacity = next_capacity;
        }
        program[length++] = (char)ch;
    }

    program[length] = '\0';
    return program;
}

int lexf(const int8_t isinput, const char *ex_filename, const char *dest_filename){
    int status = 0;
    int state = 0;
    struct lexInfo li = init_lexInfo();
    if (create_file(dest_filename, "")) return 1;
    if (create_file(DFA_LEXEME_FILENAME, "")) return 1;
    if (create_file(DFA_TOKEN_FILENAME, "")) return 1;
    #ifdef LINE_ANALYSIS
    strcpy(src_filename, ex_filename);
    #endif
    init_stat();
    if(isinput){
        char *com = read_inline_program();
        if (!com) return 1;
        size_t i = 0;
        while(com[i] != '\0'){
            status = dfa_char_analysis(com[i], &state, &li);
            i++;
	        if (status) break;
        }
        free(com);
        puts("");
    }else if(ex_filename != NULL){
        FILE *file = fopen(ex_filename, "r");
        if (!file) {
            delete_file(DFA_TOKEN_FILENAME);
            delete_file(DFA_LEXEME_FILENAME);
            __pc_error__("Error while retrieving program from file named %s", ex_filename);
            return 1;
        }
        int c;
        while((c = fgetc(file)) != EOF){
            status = dfa_char_analysis((char)c, &state, &li);
            if (status) break;
        }
	puts("");
        fclose(file);
    }
    printf("\nTokenizing the command.\n");

    if (!status) status = dfa_char_analysis('\n', &state, &li);
    if (!status && change_to_form(dest_filename, DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME) != 0) {
        __pc_error__("Error while writing lexical analysis output to %s", dest_filename);
        status = 1;
    }
    delete_file(DFA_TOKEN_FILENAME);
    delete_file(DFA_LEXEME_FILENAME);
    return status;
}
