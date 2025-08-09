#ifndef FILE_UTILS_H
#define FILE_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Create a file with given content
void create_file(const char* filename, const char* content);

// Print file content
void print_file_content(const char* filename);

// Insert new string before target string in file
void insert_before_target(const char *filename, const char *new_content, const char *target_string);

// Get nth line from file
char* get_nth_line(const char* filename, int n);

// Remove all occurrences of target string from file
void remove_string(const char* filename, const char* target, bool is_loop);

// Append content to file
void append_to_file(const char* filename, const char* content);

// Clear file content
void clear_file(const char* filename);

// Get nth word from file (space-separated)
char* get_nth_word(const char* filename, int n);

// Get line that ends with colon
char* get_line_ending_with_colon(const char* filename, int n);

// Get nth line after specific format is found
char* get_nth_line_after_format(const char* filename, const char* format, int n);

// Get error message from method at nth line
char* get_error_message(int n);

// Specialized functions for specific files
char* get_parse_line(int n);
void create_parsing_handling_file();
void append_to_parsing_handling(int mln);

// Token and indent operations
void append_indent_details(const char* filename, const char* indent);
void append_token_details(const char* filename, const char* type, const char* token);
char* read_nth_token(const char* filename, int i);
char* read_nth_indent(const char* filename, int i);

// Index-based operations
int get_indentation_value(int index);
char* get_token_string(int index);
char* get_type_value(int index);
void get_type_and_token(int index, char** type, char** token);

#endif // FILE_UTILS_H