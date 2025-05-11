#ifndef DATA_H
#define DATA_H
#define MAX 500
#define DATATYPE_INPUT_LENGTH 75
#define DATATYPE_INPUT_ARRAY_SIZE 5
#define DATATYPE_SIZE 500
#define DATATYPE_NAME_SIZE 50

typedef enum{
    t_eof, t_identifier, t_integer, t_keyword,
    //0     1               2           3
    t_op, t_punctuation, t_datatype, t_expression, t_string
    //4     5               6           7           8
} t_type;



//lexical
extern char token[MAX][MAX];
extern t_type type[MAX];
extern int token_size;
extern int total_error;
extern int indent_token[MAX];
extern char datatypes[DATATYPE_NAME_SIZE][DATATYPE_SIZE];
extern char datatype_input[DATATYPE_INPUT_LENGTH][DATATYPE_INPUT_ARRAY_SIZE][DATATYPE_SIZE];
extern int num_datatype;
// extern t_type temp;

//parse
extern int dont_compile;
extern int line_method[MAX];
extern int line_size;
extern int parametre_list[MAX][MAX];
extern char *function_id[500];
extern int function_len[500];
extern int function_size;

//compile
extern char *pgm;
extern int pgm_size;

//block analyzer
extern int block_cursor[MAX];
extern int block_cursor_size;


//functions
int num_lines(int size);
void display_token();

#endif
