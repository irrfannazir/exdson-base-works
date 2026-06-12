#ifndef PARSEH_H
#define PARSEH_H
#include "parse/parseState.h"
#include "data.h"

#define PARSE_DETAILS_MAX DIGIT*10
#define PARSE_ERROR_MESSAGE_SIZE 100

#define DEFAULT_ERROR_MESSAGE "Invalid Syntax"


extern char parsed_token[PARSE_DETAILS_MAX];
extern char working_identifier[NAME_STRLEN];
extern int lsn;
extern int ltn;

void push_to_parse_string(int index);
char *get_word_from_method(struct parseState ps); //Returns NULL if the line of method ends
char *get_meaning_from_method(int line_number);
int get_index_from_lex(int cl); //Returns -1 if the type is EOF
int next_token(int *mln); // Moves to next token for both
int skip_to_next_method(struct parseState *ps); // Moves to next method checking
int skip_to_next_line(struct parseState *ps); // Moves to next line in lex
int check_the_type(char *word, t_type type);
int append_token_details(int mln); //Saves the index in a file for parsing
int does_tree_needed(char *word); //Is word contains in tree.txt ending with ':'
int parsing_tree_analysis(struct parseState *ps, char *format, int start, int size); //Here is the function for parsing
int fputs_with_newl(const char *filename, const char *str); //Append string into the filename

int report_error_message(int mln);
void handle_identifier_declaration(int index, int method_line_num);
int try_match_type(char *word, int index, int *method_token_num);
int try_match_word(char *word, int index, int *method_token_num);
int handle_syntax_tree(char *word, int index, struct parseState *ps);
void clear_identifier_buffer();

int compare_the_word(char *word, char *token);
int save_type_in_buffer(char *buffer, int index);


static inline void reverse(char str[], int length) {
    int start = 0;
    int end = length - 1;
    while (start < end) {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
}


static inline char* itoaf(int num, char* str, int base) {
    int i = 0;
    int isNegative = 0;

    if (num == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    if (num < 0 && base == 10) {
        isNegative = 1;
        num = -num;
    }

    while (num != 0) {
        int rem = num % base;
        str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
        num /= base;
    }

    if (isNegative)
        str[i++] = '-';

    str[i] = '\0';

    reverse(str, i);

    return str;
}


#endif
