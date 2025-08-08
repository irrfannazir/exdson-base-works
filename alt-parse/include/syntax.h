#ifndef SYNTAX_H
#define SYNTAX_H
#include <stdlib.h>


static const char *syntax_dir = "alt-parse/grammar/syntax.txt";
static const char *method_dir = "alt-parse/grammar/method.txt";


char *get_line_from_syntax(char *format, int n);
char *tokenize_white_space(const char *input, int n);
char *find_command_line(char *word);


#endif