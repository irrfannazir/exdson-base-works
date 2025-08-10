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

// void remove_string(const char* filename, const char* target, bool is_loop);

// void append_to_file(const char* filename, const char* content);

// void clear_file(const char* filename);

// char* get_nth_word(const char* filename, int n);

// char* get_line_ending_with_colon(const char* filename, int n);

// char* get_nth_line_after_format(const char* filename, const char* format, int n);

// char* get_error_message(int n);

// char* get_parse_line(int n);
// void create_parsing_handling_file();
// void append_to_parsing_handling(int mln);

// void append_indent_details(const char* filename, const char* indent);
// void append_token_details(const char* filename, const char* type, const char* token);
// char* read_nth_token(const char* filename, int i);
// char* read_nth_indent(const char* filename, int i);

// int get_indentation_value(int index);
// char* get_token_string(int index);
// char* get_type_value(int index);
// void get_type_and_token(int index, char** type, char** token);

#endif // FILE_UTILS_H