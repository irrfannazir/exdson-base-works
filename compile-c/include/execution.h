#ifndef EXECUTION_H
#define EXECUTION_H
#define FUNCTION_CURSOR 0
#define CURRENT_CURSOR 1
#define CURSOR_MAX 50

extern int program_cursor[CURSOR_MAX];
extern int cursor_size;
extern int parametre_index;


void declaration_execution();
void print_execution_with_array();
void if_execution();
void else_execution();

void cursor_is_moved(int index, int value);
void add_cursor(int value);
int remove_cursor(int iterator);


#endif