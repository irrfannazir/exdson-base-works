#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "parse/parseState.h"
#include "parse/perror.h"
#include "parse/parseh.h"
#include "parse/comment.h"
#include "parse/syntax.h"
#include "common/fileh.h"
#include "common/pc_error.h"
#include "data.h"


int handle_missing_word_or_token(const char *word, int index, struct parseState *ps) {
    if (!word) {
        char temp[1024];
        sprintf(temp, "%s is unexpected", get_token(index));
        push_error(temp);
        skip_to_next_line(ps);
        return 1;
    }
    return 0;
}

void handle_identifier_declaration(int index, int method_line_num) {
    const char *syntax = read_nth_content_from_file(METHOD_DIRECTORY, method_line_num);
    if (syntax && get_type(index) == TOKEN_IDENTIFIER && strstr(syntax, DECLARATION_INSTRUCTION) != NULL){
        strcpy(working_identifier, get_token(index));
    }
}

void clear_identifier_buffer(){
    working_identifier[0] = '\0';
}


int try_match_type(char *word, int index, int *method_token_num) {
    if (check_the_type(word, get_type(index))) {
        log_debug("\tSimiliar type found\n");
        push_to_parse_string(index);
        next_token(method_token_num);
        return 1;
    }
    return 0;
}

int try_match_word(char *word, int index, int *method_token_num) {
    if (compare_the_word(word, get_token(index))) {
        log_debug("\tSimiliar word found\n");
        next_token(method_token_num);
        return 1;
    }
    return 0;
}

// Returns 1 if the tree was processed and the loop should continue,
// returns 0 if the caller should skip to next method.
int handle_syntax_tree(char *word, int index, struct parseState *ps) {
    int start = lsn + ltn - 1;   // global line+token offset
    int size;
    next_token(&(ps -> method_token_number));
    char *end = get_word_from_method(*ps);
    log_debug("\tA syntax tree found.\n");

    if (!end) {
        // No ending keyword: consume all remaining tokens
        int prev;
        while (index != -1) {
            prev = index;
            index = get_index_from_lex(1);
        }
        size = prev - start + 1;
    } else {
        // Search for the ending keyword
        while (index != -1) {
            index = get_index_from_lex(1);
            __if_it_is_null__(get_token(index),
                              printf("Error (%d): %s\n", num_lines(lsn), DEFAULT_ERROR_MESSAGE);
                              dont_compile = 1;
                              return 0,
                              "Doesn't found an keyword named %s\n", end);
            if (compare_the_word(end, get_token(index))) {
                break;
            }
        }
        if (index == -1) {
            push_error("Expected an operator.");
            skip_to_next_method(ps);
            return 1;   // error handled, continue outer loop
        }
        (ps -> method_token_number)++;
        size = index - start;
    }

    push_to_parse_string(start);
    push_to_parse_string(start + size);
    int status = parsing_tree_analysis(ps, word, start, size);
    if (status) {
        skip_to_next_method(ps);
    }
    if (end == NULL) {
        skip_to_next_line(ps);
    }
    return 1;   // tree processed, continue loop
}