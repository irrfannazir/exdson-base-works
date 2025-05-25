#ifndef UPDATE_H
#define UPDATE_H
#define MAX_TOKENS 50
#define MAX_TOKEN_LEN 500

struct parametre{
    int type;
    char name[MAX_TOKEN_LEN];
    int index;
};

char *type_check(char literal);
int special_type_check(char literal);
void print_string_array(char token[MAX_TOKENS][MAX_TOKEN_LEN], int size);
int count_char(const char *str);
void slice(char *src, int start);
void program_command_check(char *str, int i);
void print_identifier(struct parametre *a, int size);
void save_to_file(int a, int b);
void read_from_file(int *px, int *py);
void write_the_file(const char *filename, char *string_to_add, const int line_cursor);


extern char prompt[MAX_TOKEN_LEN];
extern char parametre[MAX_TOKEN_LEN];
extern char identifier_arr[MAX_TOKENS][MAX_TOKEN_LEN];
extern int identifier_num;
extern int para_num;


#endif