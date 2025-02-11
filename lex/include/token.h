#ifndef TOKEN_H
#define TOKEN_H


extern int is_eof;
extern int token_len;
extern int token_size;


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
