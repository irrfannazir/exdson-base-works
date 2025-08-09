#include "file_utils.h"
#include <sys/stat.h>

#include <stdio.h>

#define MAX_LINE_LENGTH 1024
#define MAX_WORD_LENGTH 256
#define TEMP_FILE "temp_file.tmp"

static bool file_exists(const char* filename) {
    struct stat st;
    return stat(filename, &st) == 0;
}

void insert_before_target(const char *filename, const char *new_content, const char *target_string) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "Error while reading the file %s for inserting the target\n", filename);
        return;
    }

    // Dynamically build the file content line by line
    size_t buffer_size = 4096;
    char *buffer = malloc(buffer_size);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }
    buffer[0] = '\0';

    char line[1024];
    size_t total_len = 0;
    while (fgets(line, sizeof(line), file)) {
        size_t line_len = strlen(line);
        while (total_len + line_len + 1 > buffer_size) {
            buffer_size *= 2;
            buffer = realloc(buffer, buffer_size);
            if (!buffer) {
                perror("Reallocation failed");
                fclose(file);
                return;
            }
        }
        strcat(buffer, line);
        total_len += line_len;
    }

    fclose(file);

    char *pos = strstr(buffer, target_string);
    if (!pos) {
        printf("Target string not found in file.\n");
        free(buffer);
        return;
    }

    // Reopen file for writing
    file = fopen(filename, "w");
    if (!file) {
        fprintf(stderr, "Error while writing the file %s for inserting the target\n", filename);
        free(buffer);
        return;
    }

    // Write content before target
    size_t prefix_len = pos - buffer;
    char saved = buffer[prefix_len];
    buffer[prefix_len] = '\0';
    fputs(buffer, file);
    buffer[prefix_len] = saved;

    // Insert new content
    fputs(new_content, file);

    // Write the rest of the original content
    fputs(pos, file);

    fclose(file);
    free(buffer);
}

void insert_before_string(const char* filename, const char* new_str, const char* target_str) {
    if (!file_exists(filename)) return;

    FILE* original = fopen(filename, "r");
    FILE* temp = fopen(TEMP_FILE, "w");
    
    if (original && temp) {
        char line[MAX_LINE_LENGTH];
        bool found = false;
        
        while (fgets(line, sizeof(line), original)) {
            if (!found && strstr(line, target_str)) {
                fprintf(temp, "%s\n", new_str);
                found = true;
            }
            fputs(line, temp);
        }
        
        fclose(original);
        fclose(temp);
        
        remove(filename);
        rename(TEMP_FILE, filename);
    }
}