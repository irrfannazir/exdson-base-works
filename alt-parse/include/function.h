#ifndef FUNCTION_H
#define FUNCTION_H
#include <string.h>

int contains_function(const char *str) {
    if (!str) return 0;
    return strstr(str, "$$") != NULL;
}


#endif