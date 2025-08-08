#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_nth_line_from_file(const char *filename, int n) {
    if (filename == NULL || n < 0) return NULL;

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Failed to open file");
        return NULL;
    }

    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int current_line = 0;
    char *result = NULL;

    while ((read = getline(&line, &len, fp)) != -1) {
        if (current_line == n) {
            result = malloc(read + 1); // Allocate and copy
            if (result != NULL) {
                strcpy(result, line);
            }
            break;
        }
        current_line++;
    }

    free(line);
    fclose(fp);
    return result; // NULL if not found
}
