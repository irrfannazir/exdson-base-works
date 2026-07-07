#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "parse/parseState.h"
#include "parse/parseh.h"
#include "parse/perror.h"
#include "common/fileh.h"
#include "common/pc_error.h"
#include "common/errorm.h"
#include "data.h"

char working_identifier[NAME_STRLEN] = "";

int parsef(const char *dest_filename) {
    printf("Parsing the tokens.\n");
    if (create_file(dest_filename, NULL)) return 1;
    if (create_file(SYMBOL_TABLE_FILE_NAME, "")) return 1;
    if (create_file(IC_FILENAME, "")) return 1;
    lsn = 0;
    ltn = 0;
    clear_identifier_buffer();

    struct parseState ps = init_parseState(); 
    int had_error = 0;

    char *word;
    int index;

    if(get_type(get_index_from_lex(1)) == TOKEN_NULL) skip_to_next_line(&ps);
 
    while (1) {
        word = get_word_from_method(ps);
        index = get_index_from_lex(1);

        log_debug("Analysing %s and %s(%d)\n", word, get_token(index), index);
        log_debug("Flag: %d%d%d\n",
            get_token(index) == NULL,
            index == -1,
            word == NULL
        );
 
        unsigned char flag = FLAGS_TO_INT(unsigned char,
            get_token(index) == NULL,
            index == -1,
            word == NULL
        );
        
        switch(flag){
            case 0b001:
                if(ps.method_token_number == 0) {
                    printError(ERROR_HANDLING_FILENAME,  num_lines(lsn));
                    had_error = 1;
                    ps.found_error = 1;
                    skip_to_next_line(&ps);
                    continue;
                }
                report_error_message(ps.method_line_number);
                skip_to_next_method(&ps);
                continue;
            case 0b110:
                log_debug("\tSkipping to next method\n");
                pushError(ERROR_HANDLING_FILENAME, ps.method_line_number, "%s is expected\n", word);
                skip_to_next_method(&ps);
                continue;
            case 0b111:
                log_debug("\tSkipping to next line.\n");
                if (report_error_message(ps.method_line_number)) {
                    printError(ERROR_HANDLING_FILENAME,  num_lines(lsn));
                    ps.found_error = 1;
                    had_error = 1;
                }
                skip_to_next_line(&ps);
                continue;
            case 0b100:
            case 0b101:
                log_debug("End of parsing\n");
                return had_error;
        }

        handle_identifier_declaration(index, ps.method_line_number);
        handle_undeclared_variable(index);

        if (try_match_type( word, index, &(ps.method_token_number) )) {
            if(save_type_in_buffer(ps.buffer, index)){
                __pc_error__("Buffer overflow while parsing");
                return 1;
            }
            continue;
        }
        if (try_match_word( word, index, &(ps.method_token_number) )) {
            continue;
        }
        if (does_tree_needed(word)) {
            if (handle_syntax_tree(word, index, &ps)) {
                continue;
            }
        } else {
            log_debug("\tNot this syntax\n");
            skip_to_next_method(&ps);
        }

        clear_identifier_buffer(); 
    }

    return had_error;
}

