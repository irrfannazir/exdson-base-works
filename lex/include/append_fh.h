#ifndef APPEND_FH_H
#define APPEND_FH_H
#include "../data.h"

int append_indent_to_file(const char *filename, int indent);
int append_token_to_file(const char *filename, t_type type, char *token);

#endif