#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse/parseh.h"
#include "parse/strh.h"
#include "parse/comment.h"
#include "common/errorm.h"


static inline int is_variable_redefining(){
    FILE *file = fopen(SYMBOL_TABLE_FILE_NAME, "r");
    char name[NAME_STRLEN];
    while(fgets(name, NAME_STRLEN, file)){
        trim_newline(name);
        if(strcmp(name, working_identifier) == 0){
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}

static inline int handling_declaration(int mln){
    if(
        working_identifier[0] != '\0' &&
        strstr(get_meaning_from_method(mln), DECLARATION_INSTRUCTION) != NULL
    ){
        if(is_variable_redefining()){
            pushError(ERROR_HANDLING_FILENAME, num_lines(lsn), "Redefinition of %s", working_identifier);;
            printError(ERROR_HANDLING_FILENAME, num_lines(lsn));
            dont_compile = 1;
            return 1;
        }
        fputs_with_newl(SYMBOL_TABLE_FILE_NAME, working_identifier);
    }
    return 0;
}

static inline int is_the_syntax_for_assigning(const char *syntax){
    return syntax != NULL && strstr(syntax, DECLARATION_INSTRUCTION) == NULL;
}

static inline int handling_undeclaration(int mln){
    if(
        working_identifier[0] != '\0' &&
        is_the_syntax_for_assigning(get_meaning_from_method(mln))
    ){
        pushError(ERROR_HANDLING_FILENAME, num_lines(lsn), "The variable %s is not declared", working_identifier);
        printError(ERROR_HANDLING_FILENAME, num_lines(lsn));
        dont_compile = 1;
        return 1;
    }
    return 0;
}

static inline int get_buffer_string(char *buffer, int n){
    int k = 0;
    for(int i = 0; buffer[i] != '\0'; i++){
        if(k == n) return i;
        if(buffer[i] == '|') k++;
    }
}

int method_inline_handling(struct parseState ps){
    char *meaning = get_meaning_from_method(ps.method_line_number);
    size_t ic_len = 0;
    
    if(!meaning) return 1;
    if(ps.method_line_number + ps.method_token_number == 0) return 0; 
    if(handling_declaration(ps.method_line_number)) return 1;
    if(handling_undeclaration(ps.method_line_number)) return 1;
    
    size_t meaning_len = strlen(meaning);
    char *ic_pgm = (char *) malloc( (meaning_len + BUFFER_MAX) * sizeof(char) );
    if(!ic_pgm) return 1;

    int j = -1;
    for(unsigned int i = 0 ;i < meaning_len; i++){
        switch(meaning[i]){
            case '%':
                j++;
                break;
            default:
                if(j >= 0){
                    int start = get_buffer_string(ps.buffer, j);
                    for(int j = start; ps.buffer[j] != '\0' && ps.buffer[j] != '|'; j++){
                        ic_pgm[ic_len++] = ps.buffer[j];
                    }
                    j = -1;
                }
                ic_pgm[ic_len++] = meaning[i];
                break;
        }
    }
    ic_pgm[ic_len++] = '\0';
    fputs_with_newl(IC_FILENAME, ic_pgm);
    free(ic_pgm);
    free(meaning);
    return 0;
}
