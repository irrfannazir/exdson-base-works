#include "../data.h"
#include "include/exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void create_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");  
    if (file == NULL) {
        perror("Error creating file");
        return;
    }
    fputs(content, file);
    fclose(file);
}

void print_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error reading file");
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

void compilef() {
    if(dont_compile) return;
    printf("Compiling the program\n");
    create_file(PGM_EXATED_FILE_NAME, "int main(){return 0;}");
    add_the_program();
    printf("********The output program implemented in C programming Language********\n\n");
    print_file(PGM_EXATED_FILE_NAME);
    printf("\n\n\n");
    compile_file(PGM_EXATED_FILE_NAME);
}


