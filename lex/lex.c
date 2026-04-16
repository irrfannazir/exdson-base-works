#include "include/lexh.h"
#include "include/clearf.h"
#include "include/lexState.h"
#include "include/dfah.h"
#include "filename.h"
#include "d_fh.h"
#include "../include/constants.h"
#include "../include/p_error.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

const char delimiter = ';';


int is_eof = 0;          // TODO: Debug EOF logic dependency

#define CHAR_ANAL_STATE(MSG) if(c == 's'){puts(MSG);}
#define DFA_FILENAME "dfa_n_lex.txt"
#define DFA_T_FILENAME "dfa_token.txt"
#define DFA_FINAL_FILENAME "lex.txt"

int indent = 0;
int ignore_newline = 0;
const int sitc = 2;

int dfa_char_analysis(char c, int *s){
    switch(*s){
        case 0: // Start State: After newline
            if(c == ' '){
                indent++;
            }else if(is_string_introduced(c)){
                *s = 2;
            }else if(is_char(c)){
                *s = 3;
            }else if(is_digit(c)){
                *s = 4;
            }else if(is_oper(c)){
                *s = 5;
            }else if(is_punct(c)){
                *s = 6;
            }
    
            if(c != ' ' && c != '\n' && c != delimiter){
                if (!ignore_newline) dfa_new_line(DFA_T_FILENAME, indent / sitc);
                dfa_string_conc(DFA_FILENAME, c);
            }
            break;
        case 1: //Space found
            if(c == '\n' || c == delimiter){
                *s = 0;
                indent = 0;
            }else if(is_string_introduced(c)){
                *s = 2;
            }else if(is_char(c)){
                *s = 3;
            }else if(is_digit(c)){
                *s = 4;
            }else if(is_oper(c)){
                *s = 5;
            }else if(is_punct(c)){
                *s = 6;
            }
    
            if(c != ' ' && c != '\n' && c != delimiter){
                dfa_string_conc(DFA_FILENAME, c);
            }
            break;
        case 2: // String introduced
            dfa_string_conc(DFA_FILENAME, c);
            if(is_string_introduced(c)){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, TOKEN_STRING);
                *s = 0;
            }
            break;
        case 3: // Identifier found
            if(c == ' '){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, lexeme_of_last_line(DFA_FILENAME));
                *s = 1;
            }else if(c == '\n' || c == delimiter){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, lexeme_of_last_line(DFA_FILENAME));
                indent = 0;
                *s = 0;
            }else if(is_string_introduced(c)){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, lexeme_of_last_line(DFA_FILENAME));
                dfa_string_conc(DFA_FILENAME, c);
                *s = 2;
            }else if(is_char(c) || is_digit(c)){
                dfa_string_conc(DFA_FILENAME, c);
            }else if(is_oper(c)){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, lexeme_of_last_line(DFA_FILENAME));
                dfa_string_conc(DFA_FILENAME, c);
                *s = 5;
            }else if(is_punct(c)){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, lexeme_of_last_line(DFA_FILENAME));
                dfa_string_conc(DFA_FILENAME, c);
                *s = 6;
            }else{
                *s = -1;
            }
            break;
        case 4: // Digit found
            if(c == ' '){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, TOKEN_INTEGER);
                *s = 1;
            }else if(c == '\n' || c == delimiter){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, TOKEN_INTEGER);
                indent = 0;
                *s = 0;
            }else if(is_string_introduced(c)){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, TOKEN_INTEGER);
                dfa_string_conc(DFA_FILENAME, c);
                *s = 2;
            }else if(is_oper(c)){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, TOKEN_INTEGER);
                dfa_string_conc(DFA_FILENAME, c);
                *s = 5;
            }else if(is_digit(c)){
                dfa_string_conc(DFA_FILENAME, c);
            }else if(is_punct(c)){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, TOKEN_INTEGER);
                dfa_string_conc(DFA_FILENAME, c);
                *s = 6;
            }else{
                *s = -1;
            }
            break;
        case 5: // Operator found
            if(c == ' '){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, TOKEN_OPERATOR);
                *s = 1;
            }else if(c == '\n' || c == delimiter){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, TOKEN_OPERATOR);
                indent = 0;
                *s = 0;
            }else if(is_string_introduced(c)){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, TOKEN_OPERATOR);
                dfa_string_conc(DFA_FILENAME, c);
                *s = 2;
            }else if(is_oper(c)){
                dfa_string_conc(DFA_FILENAME, c);
                *s = 5;
            }else if(is_char(c)){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, TOKEN_OPERATOR);
                dfa_string_conc(DFA_FILENAME, c);
                *s = 3;
            }else if(is_digit(c)){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, TOKEN_OPERATOR);
                dfa_string_conc(DFA_FILENAME, c);
                *s = 4;
            }else if(is_punct(c)){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, TOKEN_OPERATOR);
                dfa_string_conc(DFA_FILENAME, c);
                *s = 6;
            }else{
                *s = -1;
            }
            break;
        case 6: // Punctuator
            if(c == ' '){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, TOKEN_PUNCTUATION);
                *s = 1;
            }else if(c == '\n' || c == delimiter){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, TOKEN_PUNCTUATION);
                indent = 0;
                *s = 0;
            }else if(is_string_introduced(c)){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, TOKEN_PUNCTUATION);
                dfa_string_conc(DFA_FILENAME, c);
                *s = 2;
            }else if(is_oper(c)){
                dfa_string_conc(DFA_FILENAME, c);
                *s = 5;
            }else if(is_char(c)){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, TOKEN_PUNCTUATION);
                dfa_string_conc(DFA_FILENAME, c);
                *s = 3;
            }else if(is_digit(c)){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, TOKEN_PUNCTUATION);
                dfa_string_conc(DFA_FILENAME, c);
                *s = 4;
            }else if(is_punct(c)){
                dfa_new_token(DFA_T_FILENAME, DFA_FILENAME, TOKEN_PUNCTUATION);
                dfa_string_conc(DFA_FILENAME, c);
            }else{
                *s = -1;
            }
            break;
        case -1:
            puts("Error found!");
            *s = 0;
            break;
    }
    if (c == '{' || c == '(') ignore_newline = 1;
    if ( ignore_newline && (c == '}' || c == ')')) ignore_newline = 0;
}

int char_analysis(char c, struct lexState *s){
    if(s -> isstring){
        if(c == '"'){
            s -> isstring = 0;
        }else{
            append(c, &(s -> current_token_length));
        }
    }
    else if(c == ' '){
        if(s -> isspacef == 0 || s -> isenter == 0){
            new_token( s -> lhfn, '\0', &(s -> current_token_length));
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
        new_token( s -> lhfn, '\0', &(s -> current_token_length));
        s -> isspacef = 0;
        next_type(TOKEN_EOF);
        new_token( s -> lhfn, '\0', &(s -> current_token_length));
        newline();
        s -> isenter = 1;
    }
    else if(is_char(c)){
        s -> isspacef = 0;
        if(s -> prev == CTYPE_CHAR || s -> prev == CTYPE_DIGIT){
            append(c, &(s -> current_token_length));
        }else if(s -> prev == CTYPE_OPERATOR || s -> prev == CTYPE_PUNCT){
            new_token( s -> lhfn, c, &(s -> current_token_length));
        }
        s -> isenter = 0;
        next_type(TOKEN_IDENTIFIER);
        s -> prev = CTYPE_CHAR;
        append_indent( &(s -> space_count) );
    }
    else if(is_digit(c)){
        if(s -> isspacef){
            next_type(TOKEN_INTEGER);
            new_token( s -> lhfn, c, &(s -> current_token_length));
        }else{
            if(s -> prev == CTYPE_CHAR || s -> prev == CTYPE_DIGIT){
                append(c, &(s -> current_token_length));
            }else if(s -> prev == CTYPE_OPERATOR || s -> prev == CTYPE_PUNCT){
                new_token( s -> lhfn, c, &(s -> current_token_length));
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
            append(c, &(s -> current_token_length));
        }else if(s -> prev == CTYPE_CHAR || s -> prev == CTYPE_PUNCT || s -> prev == CTYPE_DIGIT){
            new_token( s -> lhfn, c, &(s -> current_token_length));
        }
        s -> isenter = 0;
        s -> prev = CTYPE_OPERATOR;
        next_type(TOKEN_OPERATOR);
        s -> isspacef = 0;
        append_indent( &(s -> space_count) );
    }
    else if(c == '{' || c == '('){
        new_token( s -> lhfn, c, &(s -> current_token_length));
        next_type(TOKEN_PUNCTUATION);
        s -> prev = CTYPE_PUNCT;
        s -> isenter = 0;
        s -> isspacef = 0;
        s -> iscurly++;
    }
    else if(c == '}' || c == ')'){
        new_token( s -> lhfn, c, &(s -> current_token_length));
        next_type(TOKEN_PUNCTUATION);
        s -> prev = CTYPE_PUNCT;
        s -> isspacef = 0;
        s -> isenter = 0;
        s -> iscurly--;
    }
    else if(c == '"'){
        new_token( s -> lhfn, '\0', &(s -> current_token_length));
        next_type(TOKEN_STRING);
        s -> prev = CTYPE_PUNCT;
        s -> isstring = !s -> isstring;
    }
    else if(c == '.'){
        if(s -> prev == CTYPE_DIGIT){
            append('.', &(s -> current_token_length));
        }else{
            new_token( s -> lhfn, '.', &(s -> current_token_length));
            s -> prev = CTYPE_PUNCT;
            next_type(TOKEN_PUNCTUATION);
        }
        s -> isspacef = 0;
    }
    else if(is_punct(c)){
        new_token( s -> lhfn, c, &(s -> current_token_length));
        append_indent( &(s -> space_count) );
        s -> isenter = 0;
        next_type(TOKEN_PUNCTUATION);
        s -> prev = CTYPE_PUNCT;
        s -> isspacef = 0;
    }
    else{
        s -> isspacef = 0;
        new_token( s -> lhfn, c, &(s -> current_token_length));
        next_type(TOKEN_PUNCTUATION);
        printf("Error: The unknown character '%c' is found.\n", c);
        error_found();
        append_indent( &(s -> space_count) );
        s -> isenter = 0;  // TODO: Consider recovering from error
	    return 1;
    }
    return 0;
}

int lexf(const int8_t isinput, const char *ex_filename, const char *dest_filename){
    char c;
    int cec = 0;
    int state = 0;
    clear_file(dest_filename);
    clear_file(DFA_FILENAME);
    clear_file(DFA_T_FILENAME);
    newline();
    init_stat();
    struct lexState s = initLexState(dest_filename);
    if(isinput){
        char *com;
        int i = 0;
        com = (char*)malloc(INLINE_PROGRAM_MAX_SIZE);
        if( !com ){
            printf("%s:%d: The memory allocation failed.\n", __FILE__, __LINE__);
        }
        scanf("%[^#]s", com);          // TODO: Replace with safer input method
        while(com[i] != '\0'){
            int status = char_analysis(com[i], &s);
            // printf("%c: %d -> ", com[i], state);
            dfa_char_analysis(com[i], &state);
            // printf("%d\n", state);
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
            // printf("%c: %d -> ", c, state);
            dfa_char_analysis(c, &state);
            // printf("%d\n", state);
	        if (status) cec++;
	        if (cec > 3) break;
        }
	puts("");
        fclose(file);
    }
    printf("\nTokenizing the command.\n");

    dfa_char_analysis('\n', &state);
    clear_file(DFA_FINAL_FILENAME);
    change_to_form(DFA_FINAL_FILENAME, DFA_T_FILENAME, DFA_FILENAME);

    if(c != ' ' && c != '\n' && c != delimiter){
        new_token( s.lhfn, '\0', &(s.current_token_length));
    }
    if(last_in() != TOKEN_EOF){
        next_type(TOKEN_EOF);
        new_token( s.lhfn, '\0', &(s.current_token_length));
    }
    return 0;
}
