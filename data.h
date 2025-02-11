#ifndef DATA_H
#define DATA_H
#define MAX 500

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
extern char datatypes[MAX][MAX];
extern char datatype_input[MAX][MAX];
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


//functions
int num_lines(int size);
void display_token();

#endif
