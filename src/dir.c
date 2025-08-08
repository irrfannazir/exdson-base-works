#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../data.h"

char* get_current_directory() {
    char *cwd = (char *)malloc(MAX_PATH);
    if (cwd == NULL) {
        perror("malloc error");
        return NULL;
    }

    if (getcwd(cwd, DIRECTORY_MAX_SIZE) != NULL) {
        return cwd; // Caller must free()
    } else {
        perror("getcwd error");
        free(cwd);
        return NULL;
    }
}