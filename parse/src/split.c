#include "../data.h"
#include <stdio.h>

int split_with_delimiter(int index, int size, const char delimiter){
    int i = index;
    int expected_delimiter = 0;
    while(i < index+size){
        if(expected_delimiter){
            if(token[index][0] == delimiter){
                expected_delimiter = 0;
            }
        }else{
            if(token[index][0] != delimiter){
                expected_delimiter = 1;
            }else{
                printf("Error: Not expected delimiter %c", delimiter);
                return 0;
            }
        }
        i++;
    }
    return 1;
}