#include <stdio.h>
#include "../data.h"

void create_file(const char *filename, const char *content) {
    FILE *file = fopen(filename, "w");  
    if (file == NULL) {
        __pc_error__("Error creating file named %s", filename);
        return;
    }
    if(content != NULL){
        fputs(content, file);
    }
    fclose(file);
}