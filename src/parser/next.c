#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "parse/nexth.h"
#include "parse/parseState.h"
#include "parse/perror.h"
#include "parse/syntax.h"
#include "parse/comment.h"
#include "lex/d_fh.h"
#include "common/pc_error.h"
#include "common/errorm.h"
#include "common/fileh.h"


int lsn = 0;
int ltn = 0;


int delete_space(int block_depth){
    char fn[50];
    SYMTAB_FILE_NAME(fn, block_depth);
    if(file_exists(fn)){
        delete_file(fn);
    }else{
        // log_line_analysis("\tNo file found: %s\n", fn);
    }
    return 0;
}


int method_inline_handling(struct parseState ps);

int get_index_from_lex(int cl){
    if(get_type(lsn+ltn) == TOKEN_EOF){
        return -1;
    }else{
        if(cl){
            ltn++;
        }
        return lsn+ltn-1;
    }
}

int skip_to_next_method(struct parseState *ps){
    ltn = 0;
    (ps -> method_line_number)++;
    ps -> method_token_number = 0;
    strcpy(ps -> buffer, "");
    strcpy(parsed_token, "");
    return 0;
}

#define MAX_LINE_LENGTH 1024

static inline int count_inline_comment_until(int mln){
    FILE *file = fopen(METHOD_DIRECTORY, "r");
    if (!file) {
        __pc_error__("Error while retrieving method word from the file named %s", METHOD_DIRECTORY);
        return 0;
    }

    char line[MAX_LINE_LENGTH];
    int current_line = 0;
    int inline_comment_count = 0;

    
    while (fgets(line, sizeof(line), file)) {
        if(is_inline_comment(line)) continue;
        if(is_inline_comment(strstr(line, SYNTAX_COMMENT_TOKEN))) inline_comment_count++;        
        if (current_line == mln) return inline_comment_count;
        current_line++;
    }

    fclose(file);
    return 0; 
}

int skip_to_next_line(struct parseState *ps){
    create_file(ERROR_HANDLING_FILENAME, "");
    if(ps->found_error == 0){
        method_inline_handling(*ps);
        append_token_details(ps -> method_line_number - count_inline_comment_until(ps -> method_line_number));
    }
    strcpy(parsed_token, "");

    while(get_type(lsn) != TOKEN_EOF && get_type(lsn) != TOKEN_NULL)
        lsn++;
    
    lsn++;
    ltn = 0;

    if(num_lines(lsn) > 1){
        print_line(num_lines(lsn) - 1);
        int prev_indent = get_indentation(num_lines(lsn) - 2);
        int next_indent = get_indentation(num_lines(lsn) - 1);
        if(next_indent == -1) next_indent = 0;
        if(prev_indent == -1) prev_indent = 0;
        
        if(prev_indent < next_indent){
            if( ps->space_count_for_tab == -1 ) ps->space_count_for_tab = next_indent - prev_indent;
            if( next_indent != prev_indent + ps->space_count_for_tab ){
                pushError(ERROR_HANDLING_FILENAME, 0xFFFF, "Indentation Error");
            }else{
                ps->block_depth++;
            }
        }
        
        while(prev_indent > next_indent){
            delete_space(ps->block_depth);
            ps->block_depth--;
            prev_indent -= ps->space_count_for_tab;
        }
    }

    ps -> method_token_number = 0;
    ps -> method_line_number = 0;
    ps -> reg_avail = 0;
    ps -> found_error = 0;
    strcpy(ps -> buffer, "");
    
    if(get_token(lsn) == NULL || get_type(lsn) != TOKEN_NULL) return 1;
    return 0;
}

int next_token(int *mtn){
    (*mtn)++;
    return 0;
}


int num_lines(int size){
    int res = 0;
    for(int i = 0;i < size; i++){
        if(get_type(i) == TOKEN_EOF){
            res++;
        }
    }
    return res;
}
