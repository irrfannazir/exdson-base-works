#ifndef WRITE_H
#define WRITE_H
#include "../data.h"
#include "lex/include/lexf.h"
#include "lex/include/append_fh.h"

//compile.c
void write_file(const char *filename, const char *text, int index);
char *read_file(const char *filename);

//lex.c
char* read_token(const char *filename, int i);
t_type read_type(const char *filename, int i);


#endif