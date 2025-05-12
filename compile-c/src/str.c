#include <string.h>
#include <stdlib.h>

#include <stdio.h>


// Function to append a string at a specific index
char *append_at_index(const char* original, const char* to_append, int index) {
    // Validate the input
    // printf("%s is inserting onto \t%s\t at index %d\n", original, to_append, index);
    if (!original || !to_append || index < 0 || index > strlen(original)) {
        printf("Invalid input or index.\n");
        return NULL;
    }

    // Allocate memory for the new string
    int original_len = strlen(original);
    int to_append_len = strlen(to_append);
    int new_len = original_len + to_append_len;
    int len = 0;
    char* result = (char*)malloc(new_len + 1); // +1 for the null terminator
    if (!result) {
        printf("Memory allocation failed.\n");
        return NULL;
    }

    for(int i = 0; i < index; i++){
        result[len] = original[i];
        // printf("%x\n", result[len]);
        len++;
    }

    for(int i = 0; i < to_append_len; i++){
        result[len] = to_append[i];
        // printf("%x\n", result[len]);
        len++;
    }

    for(int i = index; i < original_len; i++){
        result[len] = original[i];
        // printf("%x\n", result[len]);
        len++;
    }

    result[len] = '\0';
    original = result;
    return result;
}
