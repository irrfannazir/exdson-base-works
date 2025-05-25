#include <string.h>

int count_char(const char *str) {
    int count = 0;
    const char ch = ' ';
    while (*str != '\0') {
        if (*str == ch) {
            count++;
        }
        str++;
    }
    return count;
}

void slice(char *src, int start) {
    memmove(src, src + start, strlen(src + start) + 1);
}
