#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parse/parseState.h"
#include "parse/parseh.h"
#include "parse/perror.h"
#include "common/fileh.h"
#include "common/pc_error.h"
#include "common/errorm.h"
#include "data.h"

char working_identifier[NAME_STRLEN] = "";

void parsef(const char *src_filename, const char *dest_filename) {
    printf("Parsing the tokens.\n");
    create_file(dest_filename, NULL);
    create_file(SYMBOL_TABLE_FILE_NAME, "");
    create_file(IC_FILENAME, "");

    struct parseState ps = init_parseState(); 

    char *word;
    int index;

    if(get_type(get_index_from_lex(1)) == TOKEN_NULL) skip_to_next_line(&ps);
 
    while (1) {
        word = get_word_from_method(ps);
        index = get_index_from_lex(1);

        log_debug("Analysing %s and %s(%d)\n", word, get_token(index), index);
        uint8_t flag = FLAGS_TO_INT(uint8_t,
            get_token(index) == NULL,
            index == -1,
            word == NULL
        );
        // printf("flag: %d%d%d\n",
        //     get_token(index) == NULL,
        //     index == -1,
        //     word == NULL
        // );

        switch(flag){
            case 0b001:
                pushError(ERROR_HANDLING_FILENAME, ps.method_line_number, "%s is unexpected", strdup(get_token(index)));
                if(ps.method_token_number == 0) report_method_error(ps.method_line_number);
                skip_to_next_line(&ps);
                continue;
            case 0b110:
                log_debug("\tSkipping to next method\n");
                skip_to_next_method(&ps);
                continue;
            case 0b111:
                log_debug("\tSkipping to next line.\n");
                report_method_error(ps.method_line_number);
                skip_to_next_line(&ps);
                continue;
            case 0b100:
            case 0b101:
                log_debug("End of parsing\n");
                return;
        }

        handle_identifier_declaration(index, ps.method_line_number);
        

        if (try_match_type( word, index, &(ps.method_token_number) )) {
            if(save_type_in_buffer(ps.buffer, index)){
            __pc_error__("Buffer overflow while parsing");
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

}

