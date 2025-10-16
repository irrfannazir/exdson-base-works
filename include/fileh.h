#ifndef FILE_H
#define FILE_H
#include "../data.h"
#include "../lex/include/lexf.h"
#include "../lex/include/append_fh.h"

//compile.c
void write_file(const char *filename, const char *text, int index);
char *read_file(const char *filename);

#endif