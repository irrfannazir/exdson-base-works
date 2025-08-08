#include <stdio.h>
#include <string.h>

char *find_command_line(char *word) {
    char *marker = strstr(word, "$$");
    if (marker != NULL) {
        *(marker) = '\0';
        return marker + 2; // skip over the "$$"
    }
    return "";
}