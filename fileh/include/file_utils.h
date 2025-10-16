#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>



void create_file(const char* filename, const char* content);
void print_file_content(const char* filename);
void insert_before_target(const char *filename, const char *new_content, const char *target_string);
char* get_nth_line(const char* filename, int n, const char *keyword, int coloncount);



#endif // FILE_UTILS_H