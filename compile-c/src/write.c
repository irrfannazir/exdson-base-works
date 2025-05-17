#include "../data.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *read_file(const char *filename){
    FILE *file = fopen(filename, "r");
    char *temp = (char *)malloc(PGM_MAX);
    int size = 0;
    if (file == NULL) {
        perror("Error reading file");
        return NULL;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF){
        temp[size] = ch;
        size++;
    }
    temp[size] = '\0';
    char *pgm = malloc(size + 1);
    strcpy(pgm, temp);
    free(temp);
    fclose(file);
    return pgm;
}

void write_file(const char *filename, const char *text, int index) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char *buffer = malloc(size + strlen(text) + 1);
    if (!buffer) {
        perror("Memory error");
        fclose(file);
        return;
    }

    fread(buffer, 1, size, file);
    fclose(file);
    buffer[size] = '\0';

    if (index < 0 || index > size) index = size; // clamp index

    // Shift and insert
    char *result = malloc(size + strlen(text) + 1);
    strncpy(result, buffer, index);
    result[index] = '\0';
    strcat(result, text);
    strcat(result, buffer + index);

    file = fopen(filename, "w");
    if (!file) {
        perror("Error writing to file");
        free(buffer);
        free(result);
        return;
    }

    fputs(result, file);
    fclose(file);
    free(buffer);
    free(result);
}