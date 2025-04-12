#ifndef EXECUTION_H
#define EXECUTION_H
#define MAX 500


extern int pgm_cursor;
extern int i;
extern int block[MAX];
extern int block_size;

void declaration_execution();
void print_execution_with_array(int *include_cursor);
void if_execution();


#endif