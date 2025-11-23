#include "include/lexh.h"
#include "include/clearf.h"
#include "include/lexState.h"
#include "filename.h"
#include "d_fh.h"
#include "../include/constants.h"
#include "../include/p_error.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum{
    TOKEN_EOF,          // 0 End Of File
    TOKEN_IDENTIFIER,   // 1 Identifiers (variables, function names, etc.)
    TOKEN_INTEGER,      // 2 Integer literals (e.g., 123, 456)
    TOKEN_KEYWORD,      // 3 Keywords (e.g., if, for, while, etc.)
    TOKEN_OPERATOR,     // 4 Operators (e.g., +, -, *, /, ==)
    TOKEN_PUNCTUATION,  // 5 Punctuation (e.g., (, ), {, }, ;, ,)
    TOKEN_DATATYPE,     // 6 Datatypes (e.g., single, float)
    TOKEN_EXPRESSION,   // 7 Expressions (e.g., arithmetic, logical)
    TOKEN_STRING        // 8 String literals (e.g., "Hello")
} t_type;

const char delimiter = ';';


int token_len = 0;       // TODO: Debug usage scope
int is_eof = 0;          // TODO: Debug EOF logic dependency

#define CHAR_ANAL_STATE(MSG) if(c == 's'){puts(MSG);}

int char_analysis(char c, struct lexState *s){
    if(s -> isstring){
        if(c == '"'){
            s -> isstring = 0;
        }else{
            append(c);
        }
    }
    else if(c == ' '){
        if(s -> isspacef == 0 || s -> isenter == 0){
            new_token('\0');
        }
        if(s -> isenter){
            check_indent( &(s -> space_count) );
            s -> isenter = 1;  // TODO: Redundant assignment?
        }else{
            s -> isenter = 0;
        }
        s -> isspacef = 1;
    }
    else if(c == '\n' || c == delimiter){
        if(s -> iscurly != 0){
            return 0;
        }
        new_token('\0');
        s -> isspacef = 0;
        next_type(TOKEN_EOF);
        new_token('\0');
        newline();
        s -> isenter = 1;
    }
    else if(is_char(c)){
        s -> isspacef = 0;
        if(s -> prev == CTYPE_CHAR || s -> prev == CTYPE_DIGIT){
            append(c);
        }else if(s -> prev == CTYPE_OPERATOR || s -> prev == CTYPE_PUNCT){
            new_token(c);
        }
        s -> isenter = 0;
        next_type(TOKEN_IDENTIFIER);
        s -> prev = CTYPE_CHAR;
        append_indent( &(s -> space_count) );
    }
    else if(is_digit(c)){
        if(s -> isspacef){
            next_type(TOKEN_INTEGER);
            new_token(c);
        }else{
            if(s -> prev == CTYPE_CHAR || s -> prev == CTYPE_DIGIT){
                append(c);
            }else if(s -> prev == CTYPE_OPERATOR || s -> prev == CTYPE_PUNCT){
                new_token(c);
            }
        }
        if(prev_type() != TOKEN_IDENTIFIER){
            next_type(TOKEN_INTEGER);
        }
        s -> isspacef = 0;
        s -> isenter = 0;
        s -> prev = CTYPE_DIGIT;
        append_indent( &(s -> space_count) );
    }
    else if(is_oper(c)){
        if(s -> prev == CTYPE_OPERATOR){
            append(c);
        }else if(s -> prev == CTYPE_CHAR || s -> prev == CTYPE_PUNCT || s -> prev == CTYPE_DIGIT){
            new_token(c);
        }
        s -> isenter = 0;
        s -> prev = CTYPE_OPERATOR;
        next_type(TOKEN_OPERATOR);
        s -> isspacef = 0;
        append_indent( &(s -> space_count) );
    }
    else if(c == '{' || c == '('){
        new_token(c);
        next_type(TOKEN_PUNCTUATION);
        s -> prev = CTYPE_PUNCT;
        s -> isenter = 0;
        s -> isspacef = 0;
        s -> iscurly++;
    }
    else if(c == '}' || c == ')'){
        new_token(c);
        next_type(TOKEN_PUNCTUATION);
        s -> prev = CTYPE_PUNCT;
        s -> isspacef = 0;
        s -> isenter = 0;
        s -> iscurly--;
    }
    else if(c == '"'){
        new_token('\0');
        next_type(TOKEN_STRING);
        s -> prev = CTYPE_PUNCT;
        s -> isstring = !s -> isstring;
    }
    else if(c == '.'){
        if(s -> prev == CTYPE_DIGIT){
            append('.');
        }else{
            new_token('.');
            s -> prev = CTYPE_PUNCT;
            next_type(TOKEN_PUNCTUATION);
        }
        s -> isspacef = 0;
    }
    else if(is_punct(c)){
        new_token(c);
        append_indent( &(s -> space_count) );
        s -> isenter = 0;
        next_type(TOKEN_PUNCTUATION);
        s -> prev = CTYPE_PUNCT;
        s -> isspacef = 0;
    }
    else{
        s -> isspacef = 0;
        new_token(c);
        next_type(TOKEN_PUNCTUATION);
        printf("Error: The unknown character '%c' is found.\n", c);
        error_found();
        append_indent( &(s -> space_count) );
        s -> isenter = 0;  // TODO: Consider recovering from error
	    return 1;
    }
    return 0;
}

int lexf(const int8_t isinput, const char *ex_filename){
    char c;
    int cec = 0;
    clear_file(LEX_HANDLING_FILE_NAME);
    newline();
    init_stat();
    struct lexState s = initLexState();
    if(isinput){
        char *com;
        int i = 0;
        com = (char*)malloc(INLINE_PROGRAM_MAX_SIZE);
        if(com == NULL){
            printf("%s:%d: The memory allocation failed.\n", __FILE__, __LINE__);
        }
        scanf("%[^#]s", com);          // TODO: Replace with safer input method
        while(com[i] != '\0'){
            int status = char_analysis(com[i], &s);
            i++;
	        if (status) cec++;
	        if (cec > 3) break;
        }
        puts("");
        c = com[i];
    }else if(ex_filename != NULL){
        FILE *file = fopen(ex_filename, "r");
        if (!file) {
            __pc_error__("Error while retrieving program from file named %s", ex_filename);
            return 1;
        }
        while((c = fgetc(file)) != (signed int)0xffffffff){
            int status = char_analysis(c, &s);
	        if (status) cec++;
	        if (cec > 3) break;
        }
	puts("");
        fclose(file);
    }
    printf("\nTokenizing the command.\n");

    if(c != ' ' && c != '\n' && c != delimiter){
        new_token('\0');
    }
    if(last_in() != TOKEN_EOF){
        next_type(TOKEN_EOF);
        new_token('\0');
    }
    return 0;
}
