#ifndef LEXH_H
#define LEXH_H
#include "lexf.h"
#define PGM_MAX 500

//indent.c
void check_indent(int *space_count);
void append_indent(int *space_count);
void newline();

//character.c
int is_char(char c);
int is_digit(char c);
int is_punct(char c);
int is_oper(char c);

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