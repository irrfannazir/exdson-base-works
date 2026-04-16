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
#define DFA_LEXEME_FILENAME "dfa_lexeme.txt"
#define DFA_TOKEN_FILENAME "dfa_token.txt"

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
                if (!ignore_newline) dfa_new_line(DFA_TOKEN_FILENAME, indent / sitc);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
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
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
            }
            break;
        case 2: // String introduced
            dfa_string_conc(DFA_LEXEME_FILENAME, c);
            if(is_string_introduced(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_STRING);
                *s = 0;
            }
            break;
        case 3: // Identifier found
            if(c == ' '){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, lexeme_of_last_line(DFA_LEXEME_FILENAME));
                *s = 1;
            }else if(c == '\n' || c == delimiter){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, lexeme_of_last_line(DFA_LEXEME_FILENAME));
                indent = 0;
                *s = 0;
            }else if(is_string_introduced(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, lexeme_of_last_line(DFA_LEXEME_FILENAME));
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 2;
            }else if(is_char(c) || is_digit(c)){
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
            }else if(is_oper(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, lexeme_of_last_line(DFA_LEXEME_FILENAME));
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 5;
            }else if(is_punct(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, lexeme_of_last_line(DFA_LEXEME_FILENAME));
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 6;
            }else{
                *s = -1;
            }
            break;
        case 4: // Digit found
            if(c == ' '){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_INTEGER);
                *s = 1;
            }else if(c == '\n' || c == delimiter){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_INTEGER);
                indent = 0;
                *s = 0;
            }else if(is_string_introduced(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_INTEGER);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 2;
            }else if(is_oper(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_INTEGER);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 5;
            }else if(is_digit(c)){
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
            }else if(is_punct(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_INTEGER);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 6;
            }else{
                *s = -1;
            }
            break;
        case 5: // Operator found
            if(c == ' '){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_OPERATOR);
                *s = 1;
            }else if(c == '\n' || c == delimiter){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_OPERATOR);
                indent = 0;
                *s = 0;
            }else if(is_string_introduced(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_OPERATOR);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 2;
            }else if(is_oper(c)){
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 5;
            }else if(is_char(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_OPERATOR);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 3;
            }else if(is_digit(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_OPERATOR);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 4;
            }else if(is_punct(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_OPERATOR);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 6;
            }else{
                *s = -1;
            }
            break;
        case 6: // Punctuator
            if(c == ' '){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_PUNCTUATION);
                *s = 1;
            }else if(c == '\n' || c == delimiter){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_PUNCTUATION);
                indent = 0;
                *s = 0;
            }else if(is_string_introduced(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_PUNCTUATION);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 2;
            }else if(is_oper(c)){
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 5;
            }else if(is_char(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_PUNCTUATION);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 3;
            }else if(is_digit(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_PUNCTUATION);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 4;
            }else if(is_punct(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_PUNCTUATION);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
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
    if (*s == -1) return 1;
    return 0;
}

int lexf(const int8_t isinput, const char *ex_filename, const char *dest_filename){
    char c;
    int cec = 0;
    int state = 0;
    clear_file(dest_filename);
    clear_file(DFA_LEXEME_FILENAME);
    clear_file(DFA_TOKEN_FILENAME);
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
            int status = dfa_char_analysis(com[i], &state);
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
            int status = dfa_char_analysis(c, &state);
            if (status) cec++;
	        if (cec > 3) break;
        }
	puts("");
        fclose(file);
    }
    printf("\nTokenizing the command.\n");

    dfa_char_analysis('\n', &state);
    change_to_form(dest_filename, DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME);

    if(c != ' ' && c != '\n' && c != delimiter){
        new_token( s.lhfn, '\0', &(s.current_token_length));
    }
    if(last_in() != TOKEN_EOF){
        next_type(TOKEN_EOF);
        new_token( s.lhfn, '\0', &(s.current_token_length));
    }
    return 0;
}
