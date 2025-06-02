#ifndef LEXH_H
#define LEXH_H

//indent.c
void add_indent(int *space_count);
void clear_indent(int *iscolonfound);

//character.c
int is_char(char c);
int is_digit(char c);
int is_punct(char c);
int is_oper(char c);

//keyword.c
void filter_keyword();

//token.c
extern int is_eof;
extern int token_len;


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