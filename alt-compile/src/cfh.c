#include <stdlib.h>
#include <stdio.h>
#include "../data.h"

void create_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");  
    if (file == NULL) {
        __pc_error__("Error creating file named %s", filename);
        return;
    }
    fputs(content, file);
    fclose(file);
}

void print_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        __pc_error__("Error reading file named %s", filename);
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF)
        putchar(ch);
    putchar('\n');
    fclose(file);
}

void compile_file(const char *filename){
    char compile_command[256];
    snprintf(compile_command, sizeof(compile_command), "gcc %s -o out", filename);
    int result = system(compile_command);

    if (result == 0) {
        printf("Compilation successful. Executable created as 'out'.\n");
    } else {
        printf("Compilation failed.\n");
    }
}


