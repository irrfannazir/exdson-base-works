#include <stdio.h>
#include <string.h>

// Function to save three integers to a file
void save_to_file(int a, int b) {
    const char *filename = "data.txt";
    FILE *file = fopen(filename, "w");  // Open file in write mode
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(file, "%d %d", a, b); // Write integers to file
    fclose(file);  // Close the file
}

// Function to read three integers from a file
void read_from_file(int *px, int *py) {
    const char *filename = "data.txt";
    FILE *file = fopen(filename, "r");  // Open file in read mode
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    int x, y;
    if (fscanf(file, "%d %d", &x, &y) == 2) {  // Read integers
        printf("Read from file: %d, %d\n", x, y);
    } else {
        printf("Error reading data from file!\n");
    }
    *px = x;
    *py = y;
    fclose(file);  // Close the file
}



void write_the_file(const char *filename, char *string_to_add, const int line_cursor){
    FILE *fp;
    char line[5000];
    char res[10000];
    int i = 0;
    strcpy(res, "");
    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Error.\n");
        return;
    }
    while(fgets(line, 500, fp) != NULL){
        if(i == line_cursor){
            strcat(res, string_to_add);
        }
        strcat(res, line);
        i++;
    }
    fclose(fp);
    fp = fopen(filename, "w");
    if(fp == NULL){
        printf("Error.\n");
        return;
    }
    if(fputs(res, fp) == EOF){
        printf("Error putting file.\n");
        fclose(fp);
    }
    fclose(fp);
    printf("%s: File updated successfully.\n", filename);
    return;
}
