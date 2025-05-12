#include "../data.h"
#include "include/exec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *pgm;

void create_and_compile_file(const char *filename, char *content) {
    // Open the file for writing ("w" mode will create the file if it doesn't exist)
    FILE *file = fopen(filename, "w");

    if (file == NULL) {
        // Error handling if the file cannot be opened
        printf("Error opening file for writing.\n");
        return;
    }

    // Write content to the file
    printf("********The output program implemented in C programming Language********");
    printf("\n\n%s\n\n\n", content);
    fprintf(file, "%s", content);
    
    // Close the file
    fclose(file);

    printf("C file created successfully.\n");

    // Compile the file using the system's compiler (gcc)
    char compile_command[256];
    snprintf(compile_command, sizeof(compile_command), "gcc %s -o out", filename);

    // Execute the compile command
    int result = system(compile_command);

    // Check if compilation was successful
    if (result == 0) {
        printf("Compilation successful. Executable created as 'out'.\n");
    } else {
        printf("Compilation failed.\n");
    }
}

void compilef() {
    if(dont_compile) return;
    printf("Compiling the program\n");
    const char *filename = "program.c";  // Name of the C file to create
    pgm = (char *)malloc(PGM_MAX + 1);
    add_the_program();
    // Call the function to create the file and compile it
    create_and_compile_file(filename, pgm);
}


