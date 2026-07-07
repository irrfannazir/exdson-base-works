#include "lex/dfah.h"
#include "lex/lexInfo.h"
#include "lex/lexh.h"
#include "lex/lerror.h"
#include <stdint.h>
#include <stdio.h>

const char delimiter = ';';
const int sitc = 2;

int dfa_char_analysis(char c, int *s, struct lexInfo *li){
    switch(*s){
        case 0: // Start State: After newline
            if(c == LEX_VALUE_FIRST_SYMBOL){
                *s = 7;
                break;
            }else if(c == ' '){
                (li -> indent)++;
            }else if(c == '\n' || c == delimiter){
                ;
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
            }else{
                charerror(c);
                return 1;
            }
    
            if(c != ' ' && c != '\n' && c != delimiter){
                if (!(li -> ignore_newline)) dfa_new_line(DFA_TOKEN_FILENAME, (li -> indent) / sitc);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
            }
            break;
        case 1: //Space found
            if(c == LEX_VALUE_FIRST_SYMBOL){
                *s = 7;
                break;
            }else if(c == ' '){
                ;
            }else if(c == '\n' || c == delimiter){
                *s = 0;
                (li -> indent) = 0;
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
            }else{
                charerror(c);
                return 1;
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
            if(c == LEX_VALUE_FIRST_SYMBOL){
                *s = 7;
            }else if(c == ' '){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, lexeme_of_last_line(DFA_LEXEME_FILENAME));
                *s = 1;
            }else if(c == '\n' || c == delimiter){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, lexeme_of_last_line(DFA_LEXEME_FILENAME));
                (li -> indent) = 0;
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
                charerror(c);
                return 1;
            }
            break;
        case 4: // Digit found
            if(c == '.'){
                if(li->point == 0){
                    li->point = 1;
                    dfa_string_conc(DFA_LEXEME_FILENAME, c);
                    break;
                }else{
                    lexerror("Invalid floating value");
                    return 1;
                }
            }
            if(c == ' '){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_INTEGER);
                *s = 1;
                li->point = 0;
            }else if(c == '\n' || c == delimiter){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_INTEGER);
                (li -> indent) = 0;
                *s = 0;
                li->point = 0;
            }else if(is_string_introduced(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_INTEGER);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 2;
                li->point = 0;
            }else if(is_char(c)){
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                int size = size_of_last_line(DFA_LEXEME_FILENAME);
                char last_token[size + 1];
                fget_last_line(DFA_LEXEME_FILENAME, last_token, size + 1);
                const char *text = "Identifier %.*s is recognized as invalid";
                size_t msg_len = snprintf(NULL, 0, text, size, last_token) + 1;
                char error_msg[msg_len];
                snprintf(error_msg, msg_len, text, size, last_token);
                lexerror(error_msg);
                li->point = 0;
                *s = 0;
            }else if(is_digit(c)){
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
            }else if(is_oper(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_INTEGER);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 5;
                li->point = 0;
            }else if(is_punct(c)){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_INTEGER);
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
                *s = 6;
                li->point = 0;
            }else{
                charerror(c);
                return 1;
            }
            break;
        case 5: // Operator found
            if(c == LEX_VALUE_FIRST_SYMBOL){
                *s = 7;
            }else if(c == ' '){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_OPERATOR);
                *s = 1;
            }else if(c == '\n' || c == delimiter){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_OPERATOR);
                (li -> indent) = 0;
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
                charerror(c);
                return 1;
            }
            break;
        case 6: // Punctuator
            if(c == LEX_VALUE_FIRST_SYMBOL){
                *s = 7;
            }else if(c == ' '){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_PUNCTUATION);
                *s = 1;
            }else if(c == '\n' || c == delimiter){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_PUNCTUATION);
                (li -> indent) = 0;
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
                charerror(c);
                return 1;
            }
            break;
        case 7: // New expressions
            if(c == LEX_VALUE_SECOND_SYMBOL){
                *s = 8;
            }else{
                lexerror("The '{' is not found.");
            }
            break;
        case 8:
            if(c == LEX_VALUE_END_SYMBOL){
                dfa_new_token(DFA_TOKEN_FILENAME, DFA_LEXEME_FILENAME, TOKEN_INTEGER);
                *s = 1;
            }else{
                dfa_string_conc(DFA_LEXEME_FILENAME, c);
            }
            break;
        case -1:
            puts("Lex Terminated!");
            return 1;
    }
    if (c == '{' || c == '(') (li -> ignore_newline) = 1;
    if ( (li -> ignore_newline) && (c == '}' || c == ')') ) (li -> ignore_newline) = 0;
    return 0;
}