#ifndef FILE_H
#define FILE_H
#include <stdio.h>
#include <stdbool.h>
#include <sys/stat.h>
#include "../data.h"
#include "../lex/include/clearf.h"
#include "../lex/include/append_fh.h"

#define MAX_WORD_LENGTH 256
#define MAX_LINE_LENGTH MAX_WORD_LENGTH*10

void insert_before_target(const char *filename, const char *new_content, const char *target_string);
char* get_nth_line(const char* filename, int n, const char *keyword);

static inline bool file_exists(const char* filename) {
    struct stat st;
    return stat(filename, &st) == 0;
}

static inline void create_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        __pc_error__("Error creating file named %s", filename);
        return;
    }
    
    if (content != NULL) {
        if (fputs(content, file) == EOF) {
            __pc_error__("Error writing content to file %s", filename);
        }
    }
    
    if (fclose(file) != 0) {
        __pc_error__("Error closing file %s", filename);
    }
}

static inline void print_file_content(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file) {
        char line[MAX_LINE_LENGTH];
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
        }
        fclose(file);
    }
}

#endif