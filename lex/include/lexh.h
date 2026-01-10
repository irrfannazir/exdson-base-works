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


void new_token(char c);
void append(char c);
void error_found();
int last_in();
void next_type(int next);
int size();
int prev_type();
int num_lines(int size);
void display_token();


#endif