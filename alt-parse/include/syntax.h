#ifndef SYNTAX_H
#define SYNTAX_H
#include <stdlib.h>


static const char *syntax_dir = "grammar/syntax.txt";
static const char *method_dir = "grammar/method.txt";


char *tokenize_white_space(const char *input, int n);
char *find_command_line(char *word);


#endif