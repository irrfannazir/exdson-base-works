#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse/inlinef.h"

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
    
    size_t meaning_len = strlen(meaning);
    char *ic_pgm = (char *) malloc( (strlen(meaning) + BUFFER_MAX) * sizeof(char) );
    if(!ic_pgm) return 1;

    int j = -1;
    int k;
    for(int i = 0 ;i < strlen(meaning); i++){
        switch(meaning[i]){
            case '%':
                j++;
                break;
            default:
                if(j >= 0){
                    int start = get_buffer_string(ps.buffer, j);
                    for(int j = start; j < ps.buffer[j] != '\0' && ps.buffer[j] != '|'; j++){
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
