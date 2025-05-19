#include "../include/execution.h"
#include <stdio.h>

void cursor_is_moved(int index, int value){
    int current = program_cursor[index];
    for(int i = 0; i < cursor_size; i++){
        if(program_cursor[i] >= current){
            program_cursor[i] += value;
        }
    }
}


void add_cursor(int value){
    program_cursor[cursor_size] = program_cursor[CURRENT_CURSOR];
    program_cursor[CURRENT_CURSOR] -= value;
    cursor_size++;
}

int remove_cursor(){
    cursor_size--;
    program_cursor[CURRENT_CURSOR] = program_cursor[cursor_size];
}
