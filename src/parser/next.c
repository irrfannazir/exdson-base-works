#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "lex/d_fh.h"
#include "parse/parseState.h"
#include "parse/parseh.h"
#include "parse/inlinef.h"
#include "parse/perror.h"
#include "data.h"


int lsn = 0;
int ltn = 0;


int get_index_from_lex(int cl){
    log_debug("lsn = %d; ltn = %d", lsn, ltn);
    if(get_type(lsn+ltn) == TOKEN_EOF){
        log_debug("\t==> <%s, %d>\n", get_token(-1), get_type(-1));
        return -1;
    }else{
        if(cl){
            ltn++;
        }
        log_debug("\t==> <%s, %d>\n", get_token(lsn+ltn-1), get_type(lsn+ltn-1));
        return lsn+ltn-1;
    }
}

static inline int is_error_found_in_line(int mln){
    char *error_message = get_error_message_from_method(mln);
    if(error_message != NULL){
        push_error(error_message);
    }
    free(error_message);
    if( error ){
        printf("Error (%d): ", num_lines(lsn));
        dont_compile = 1;
        print_error();
        return 0;
    }
    return 1;
}

int skip_to_next_method(struct parseState *ps){
    ltn = 0;
    (ps -> method_line_number)++;
    ps -> method_token_number = 0;
    strcpy(ps -> buffer, "");
    current_error_priority = error_priority;
    strcpy(parsed_token, "");
    return 0;
}

int skip_to_next_line(struct parseState *ps){
    
    if(is_error_found_in_line(ps -> method_line_number)){
        method_inline_handling(*ps);
        append_token_details(ps -> method_line_number);
    }
    strcpy(parsed_token, "");

    while(get_type(lsn) != TOKEN_EOF && get_type(lsn) != TOKEN_NULL)
        lsn++;
    
    lsn++;
    ltn = 0;
    ps -> method_token_number = 0;
    ps -> method_line_number = 0;
    ps -> reg_avail = 0;
    strcpy(ps -> buffer, "");
    
    if(get_token(lsn) == NULL || get_type(lsn) != TOKEN_NULL) return 1;
    return 0;
}

int next_token(int *mtn){
    (*mtn)++;
    error_priority++;
    return 0;
}

//To count number of lines
int num_lines(int size){
    int res = 0;
    for(int i = 0;i < size; i++){
        if(get_type(i) == TOKEN_EOF){
            res++;
        }
    }
    return res;
}