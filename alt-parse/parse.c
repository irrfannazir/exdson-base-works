#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../data.h"
#include "parseh.h"
#include "pdebug.h"
#include "../utils/p_error.h"

#define DEFAULT_ERROR_MESSAGE "Invalid Syntax"

int isparsing = 1;

void parsef(){
    printf("Alternative parsing.\n");
    create_the_parser_file();
    int mln = 0;
    int mtn = 0;
    while(1){
        char *word = get_word_from_method(mln, mtn);
        int index = get_index_from_lex(1);
        #ifdef P_PARSE_DEBUG_MODE
          if(word == NULL){
              printf(";\n");
          }
        #endif
        #ifdef P_PARSE_DEBUG_MODE
        printf("Analyzing %s and %s\n", word, get_token(index));
        #endif
        if (get_token(index) == NULL && word == NULL) {
            next_line(&mln, &mtn);
            #ifdef P_PARSE_DEBUG_MODE
            printf("\tSkipping to next line.\n");
            #endif
            if (get_token(get_index_from_lex(0)) == NULL) {
                #ifdef P_PARSE_DEBUG_MODE
                 printf("End of parsing\n");
                #endif
                return;
            }
            continue;
        }else if (index == -1 || word == NULL){
            if(word == NULL){
                push_error("Unexpected token found");
                isparsing++;
                next_line(&mln, &mtn);
                continue;
            }
            #ifdef P_PARSE_DEBUG_MODE
             printf("\tSkipping to next method\n");
            #endif
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


        if( check_the_type(word, get_type(index)) ){
            #ifdef P_PARSE_DEBUG_MODE
             printf("\tSimiliar type found\n");
            #endif
            push_to_parse_string(index);
            next_token(&mtn);
        }else if( compare_the_word(word, get_token(index))){
            #ifdef P_PARSE_DEBUG_MODE
             printf("\tSimiliar word found\n");
            #endif
            next_token(&mtn);
        }else if( does_tree_needed(word) ){
            #ifdef P_PARSE_DEBUG_MODE
             printf("\tA syntax tree found.\n");
            #endif
            int start = lsn + ltn - 1;
            int size;
            next_token(&mtn);
            char *end = get_word_from_method(mln, mtn);
            if(end == NULL){
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
            #ifdef P_PARSE_DEBUG_MODE
             printf("\tNot this syntax\n");
            #endif
            next_method(&mln, &mtn);
        }
        isparsing++;
    }
}