#include <stdio.h>
#include <stdlib.h>

char* read_file_into_buffer(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    // Seek to end to get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // Allocate buffer (+1 for null terminator)
    char* content = (char*)malloc(file_size + 1);
    if (content == NULL) {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    // Read entire file
    size_t bytes_read = fread(content, 1, file_size, file);
    if (bytes_read != file_size) {
        fclose(file);
        free(content);
        fprintf(stderr, "Error reading file\n");
        return NULL;
    }

    // Null-terminate the string
    content[bytes_read] = '\0';

    fclose(file);
    return content;
}