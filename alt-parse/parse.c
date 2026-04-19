#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parseh.h"
#include "comment.h"
#include "syntax.h"
#include "perror.h"
#include "../data.h"
#include "../include/pc_error.h"
#include "../include/fileh.h"

#define DEFAULT_ERROR_MESSAGE "Invalid Syntax"

char working_identifier[NAME_STRLEN] = "";


void parsef(const char *src_filename, const char *dest_filename){
    printf("Alternative parsing.\n");
    create_file(dest_filename, NULL);
    create_file(DEFINED_IDENTIFIER_FILE_NAME, "");
    int mln = 0;
    int mtn = 0;
    while(1){
        char *word = get_word_from_method(mln, mtn);
        int index = get_index_from_lex(1);

        log_debug("Analysing %s and %s\n", word, get_token(index));
        
        if (get_token(index) == NULL && word == NULL) {
            next_line(&mln, &mtn);
        
            log_debug("\tSkipping to next line.\n");
        
            if ( !get_token(get_index_from_lex(0)) ) {
                
                log_debug("End of parsing\n");
                return;
            }
            continue;
        }else if (index == -1 || word == NULL){
            if( !word ){
                char temp[1024];
                sprintf(temp, "%s is unexpected", get_token(index));
                push_error(temp);
                next_line(&mln, &mtn);
                continue;
            }
        
            log_debug("\tSkipping to next method\n");
            next_method(&mln, &mtn);
            continue;
        }

        if (word == NULL && (index == -1 || mtn == 0)) {
            const char *msg = get_error_message_from_method(mln);
            if (msg != NULL) {
                printf("Error (%d): %s\n", num_lines(lsn) + 1, msg);
            } else {
                printf("Error (%d): %s\n", num_lines(lsn) + 1, DEFAULT_ERROR_MESSAGE);
            }
            dont_compile = 1;

            if (next_line(&mln, &mtn)) {
                // End of file
                break;
            }
            continue;
        }

        if (index == -1 || get_token(index) == NULL) {
            next_method(&mln, &mtn);
            continue;
        }

        // save identifier for declaration purpose
        if (get_type(index) == TOKEN_IDENTIFIER && contains_function(read_nth_content_from_file(METHOD_DIRECTORY, mln))){
            strcpy(working_identifier, get_token(index));
        }

        if( check_the_type(word, get_type(index)) ){
            
            log_debug("\tSimiliar type found\n");
            push_to_parse_string(index);
            next_token(&mtn);

        }else if( compare_the_word(word, get_token(index))){
            
            log_debug("\tSimiliar word found\n");        
            next_token(&mtn);

        }else if( does_tree_needed(word) ){
        
            int start = lsn + ltn - 1;
            int size;
            next_token(&mtn);
            char *end = get_word_from_method(mln, mtn);
            log_debug("\tA syntax tree found.\n");
            
            if( !end ){
                int prev;
                while(index != -1){
                    prev = index;
                    index = get_index_from_lex(1);
                }
                size = prev - start + 1;
            }else{
                while( index != -1 ){
                    index = get_index_from_lex(1);
                    __if_it_is_null__(get_token(index), printf("Error (%d): %s\n", num_lines(lsn), DEFAULT_ERROR_MESSAGE);dont_compile = 1;return, "Doesn't found an keyword named %s\n", end);
                    if( compare_the_word(end, get_token(index)) ){
                        break;
                    }
                }
                if(index == -1){
                    push_error("Expected an operator.");
                    next_method(&mln, &mtn);
                    continue;
                }
                mtn++;
                size = index - start;
            }
            push_to_parse_string(start);
            push_to_parse_string(start+size);
            int status = parsing_tree_analysis(word, start, size);
            if(status){
                next_method(&mln, &mtn);
            }
            if(end == NULL){
                next_line(&mln, &mtn); 
            }
        }
        else{
            log_debug("\tNot this syntax\n");
            next_method(&mln, &mtn);
        }
    }
}