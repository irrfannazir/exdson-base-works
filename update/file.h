#ifndef FILE_H
#define FILE_H
#define FINAL_RESULT_MAX 2000
#define MAX 500


extern char var[20][MAX];
extern int var_len;
extern int var_index[MAX];

extern int isand;



void readFromFile(int *px, int *py);
void saveToFile(int a, int b);
void write_the_file(const char *filename, char *string_to_add, const int line_cursor);

void add_body_in_parse(int fno, int vno, int cno);
void add_body_in_declare_header(int fno, int vno);
void add_body_in_declare(int fno, int vno, int cno);

int check_var(char *str);
char *datatype(char token);


int do_find_the_type(char *syntax, int i, char *conditions, char *parametres, int index_num, int para_num);
void do_compare_the_str(char *comp, char *cond, int index_num);

void analyse_the_query(char *conditions, char *parametres);
void analyse_the_input(int cno);


#endif