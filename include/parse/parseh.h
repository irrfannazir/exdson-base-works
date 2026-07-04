#ifndef PARSEH_H
#define PARSEH_H
#include "parse/parseState.h"
#include "data.h"


extern char working_identifier[NAME_STRLEN];
extern int lsn;
extern int ltn;

void push_to_parse_string(int index);
char *get_word_from_method(struct parseState ps);
char *get_meaning_from_method(int line_number);
int get_index_from_lex(int cl); //Returns -1 if the type is EOF
int next_token(int *mln); // Moves to next token for both
int skip_to_next_method(struct parseState *ps); // Moves to next method checking
int skip_to_next_line(struct parseState *ps); // Moves to next line in lex
int token_to_type(char *syn);
int does_tree_needed(char *word); //Is word contains and ending with ':'
int parsing_tree_analysis(struct parseState *ps, char *format, int start, int size); //Here is the function for parsing
int fputs_with_newl(const char *filename, const char *str); //Append string into the filename

int report_error_message(int mln);
void handle_identifier_declaration(int index, int method_line_num);
void handle_undeclared_variable(int index);
int try_match_type(char *word, int index, int *method_token_num);
int try_match_word(char *word, int index, int *method_token_num);
int handle_syntax_tree(char *word, int index, struct parseState *ps);
void clear_identifier_buffer();

int compare_the_word(char *word, char *token);
int save_type_in_buffer(char *buffer, int index);




#endif
