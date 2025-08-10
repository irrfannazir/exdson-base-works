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