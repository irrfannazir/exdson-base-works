#include <stdio.h>
#include "include/file_utils.h"

int main(){
    printf("%s", get_nth_line("p.txt", 1, NULL));
    return 0;
}