#include "../data.h"
#include "include/debug.h"
#include <stdio.h>
#include <stdarg.h>


void debug_the_false_arg(int count, ...){
    va_list args;
    int i, sum = 0;
    va_start(args, count);
    printf("The errors in the parsing analyzer:");
    for (i = 0; i < count; i++) {
        int val = va_arg(args, int) ;
        if(val == 0){
            printf("\t%d", i+1);
        }
    }
    printf("\n");
    va_end(args);

}


void debug_the_tokens(char *comment, int index, int size){
    printf("%s:\n", comment);
    for (int i = index; i < index+size; i++)
    {
        printf("%s\n", token[i]);
    }
}
