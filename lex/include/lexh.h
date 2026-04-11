#ifndef LEXH_H
#define LEXH_H
#define INLINE_PROGRAM_MAX_SIZE 500

static inline int is_char(char c) {
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
}

static inline int is_digit(char c) {
    return (c >= '0' && c <= '9');
}

static inline int is_punct(char c) {
    const char *punct = "(){}[].,:'\"";
    for (int i = 0; punct[i] != '\0'; i++) {
        if (punct[i] == c)
            return 1;
    }
    return 0;
}

static inline int is_oper(char c) {
    const char *operators = "+-*/=<>";
    for (int i = 0; operators[i] != '\0'; i++) {
        if (operators[i] == c)
            return 1;
    }
    return 0;
}


//indent.c
void check_indent(int *space_count);
void append_indent(int *space_count);
void newline();

//token.c
extern int is_eof;


void new_token(const char *lhfn, char c, int *current_token_length);
void append(char c, int *current_token_length);
void error_found();
int last_in();
void next_type(int next);
int size();
int prev_type();
int num_lines(int size);
void display_token();

<<<<<<< Updated upstream
=======

//dfa


int lexeme_of_last_line(const char *filename);
int dfa_new_token(const char *filename, t_type value);
int dfa_string_conc(const char *filename, char c);

#define DFA_FILENAME "dfa_lex.txt"
static inline int dfa_char_analysis(char c, int *s){
    switch(*s){
        case 0: // Start State
            if(is_string_introduced(c)){
                *s = 1;
            }else if(is_char(c)){
                *s = 2;
            }else if(is_digit(c)){
                *s = 3;
            }else if(is_oper(c)){
                *s = 4;
            }
            if(c != ' ' && c != '\n' && c != delimiter){
                dfa_string_conc(DFA_FILENAME, c);
            }
            break;
        case 1: // String introduced
            dfa_string_conc(DFA_FILENAME, c);
            if(is_string_introduced(c)){
                dfa_new_token(DFA_FILENAME, TOKEN_STRING);
                *s = 0;
            }
            break;
        case 2: // Identifier found
            if(c == ' '){
                dfa_new_token(DFA_FILENAME, lexeme_of_last_line(DFA_FILENAME));
                *s = 0;
            }else if(c == '\n' || c == delimiter){
                dfa_new_token(DFA_FILENAME, lexeme_of_last_line(DFA_FILENAME));
                *s = 0;
            }else if(is_char(c) || is_digit(c)){
                dfa_string_conc(DFA_FILENAME, c);
            }else if(is_oper(c)){
                dfa_new_token(DFA_FILENAME, lexeme_of_last_line(DFA_FILENAME));
                dfa_string_conc(DFA_FILENAME, c);
                *s = 4;
            }else{
                *s = -1;
            }
            break;
        case 3: // Digit found
            if(c == ' '){
                dfa_new_token(DFA_FILENAME, TOKEN_INTEGER);
                *s = 0;
            }else if(c == '\n' || c == delimiter){
                dfa_new_token(DFA_FILENAME, TOKEN_INTEGER);
                *s = 0;
            }else if(is_punct(c)){
                dfa_new_token(DFA_FILENAME, TOKEN_INTEGER);
                dfa_string_conc(DFA_FILENAME, c);
                *s = 4;
            }else if(is_digit(c)){
                dfa_string_conc(DFA_FILENAME, c);
            }else{
                *s = -1;
            }
            break;
        case 4: // Operator found
            if(c == ' '){
                dfa_new_token(DFA_FILENAME, TOKEN_OPERATOR);
                *s = 0;
            }else if(c == '\n' || c == delimiter){
                dfa_new_token(DFA_FILENAME, TOKEN_OPERATOR);
                *s = 0;
            }else if(is_oper(c)){
                dfa_string_conc(DFA_FILENAME, c);
                *s = 4;
            }else if(is_char(c)){
                dfa_new_token(DFA_FILENAME, TOKEN_OPERATOR);
                dfa_string_conc(DFA_FILENAME, c);
                *s = 2;
            }else if(is_digit(c)){
                dfa_new_token(DFA_FILENAME, TOKEN_OPERATOR);
                dfa_string_conc(DFA_FILENAME, c);
                *s = 3;
            }else{
                *s = -1;
            }
            break;
        case -1:
            puts("Error found!");
            break;
    }
}

>>>>>>> Stashed changes

#endif