#ifndef PARSEH_H
#define PARSEH_H
#include "../data.h"

#define PARSE_DETAILS_MAX DIGIT*10
#define PARSE_ERROR_MESSAGE_SIZE 100

// int get_line_size(FILE *file);
// int datatype_to_type(char *syn);
// int print_token();

/*
    method: TD TI = EXPRESSION
    lex:    single a = 3 + 4
            0      1 2 3 4 5 6        
*/

extern int isparsing;
extern char parsed_token[PARSE_DETAILS_MAX];
extern int error_priority;
extern int current_error_priority;
extern char *error;
extern int lsn;
extern int ltn;

int create_the_parser_file();
void push_to_parse_string(int index);
char *get_word_from_method(int line_number, int token_number); //Returns NULL if the line of method ends
char *get_error_message_from_method(int line_number);
int get_index_from_lex(int cl); //Returns -1 if the type is EOF
int next_line(int *mln, int *mtn); // Moves to next line in lex
int is_eof_lex(); // return 1 if eof occurs in lex
int next_token(); // Moves to next token for both
int next_method(); // Moves to next method checking
int check_the_type(char *word, t_type type);
int append_token_details(int mln); //Saves the index in a file for parsing
int compare_the_word(char *word, char *token); //Compares the 
int does_tree_needed(char *word); //Is word contains in tree.txt ending with ':'
int parsing_tree_analysis(char *format, int start, int size); //Here is the function for parsing

void push_error(const char *temp);
int print_error();


//Debugging



#endif