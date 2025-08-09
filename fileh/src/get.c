#include "../include/file_utils.h"
#include <sys/stat.h>

static bool file_exists(const char* filename) {
    struct stat st;
    return stat(filename, &st) == 0;
}

char* get_nth_line(const char* filename, int n) {
    if (!file_exists(filename)) return NULL;

    FILE* file = fopen(filename, "r");
    if (!file) return NULL;

    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int current_line = 0;
    char* result = NULL;

    while ((read = getline(&line, &len, file)) != -1) {
        if (current_line == n) {
            result = strdup(line);
            break;
        }
        current_line++;
    }

    free(line);
    fclose(file);
    return result;
}