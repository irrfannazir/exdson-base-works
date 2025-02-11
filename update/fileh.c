#include <stdio.h>
#include "file.h"

// Function to save three integers to a file
void saveToFile(int a, int b) {
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
void readFromFile(int *px, int *py) {
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