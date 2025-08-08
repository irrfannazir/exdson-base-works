#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "syntax.h"
#include "../data.h"

#define MAX_LINE_LENGTH 256

// Remove newline characters and return new length
size_t trim_newline(char *line) {
    size_t len = strlen(line);
    while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r')) {
        line[--len] = '\0';
    }
    return len;
}

// Check if line is empty or only whitespace
int is_blank_line(const char *line) {
    while (*line) {
        if (!isspace((unsigned char)*line)) return 0;
        line++;
    }
    return 1;
}

// Skip leading spaces and tabs
char *trim_leading_whitespace(char *line) {
    while (*line && isspace((unsigned char)*line)) {
        line++;
    }
    return line;
}

char *get_line_from_syntax(char *format, int n) {
    FILE *file = fopen(syntax_dir , "r");
    if (!file) {
        __pc_error__("Error while retrieving line from file named %s", syntax_dir);
        return NULL;
    }
    if (!format){
        __pc_error__("Got an empty format.\n");
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    int found_format = 0;
    int current_line = 0;


    while (fgets(line, sizeof(line), file)) {
        size_t len = trim_newline(line);

        // Check for format block like EXPRESSION:
        if (len > 0 && line[len - 1] == ':') {
            char name[MAX_LINE_LENGTH];
            strncpy(name, line, len - 1);
            name[len - 1] = '\0';
            if (strcmp(name, format) == 0) {
                found_format = 1;
                current_line = 0;
                continue;
            }

            // Exit block if another block starts
            if (found_format) break;
        }

        if (found_format && !is_blank_line(line)) {
            if (current_line == n) {
                fclose(file);
                // Strip leading whitespace before returning
                return strdup(trim_leading_whitespace(line));
            }
            current_line++;
        }
    }

    fclose(file);
    return NULL;
}

