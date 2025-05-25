#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include "update.h"
#define FINAL_RESULT_MAX 1000
#define MAX 1000


char condition[MAX_TOKEN_LEN] = "";
char parametres[MAX_TOKEN_LEN] = "";
char prompt[MAX_TOKEN_LEN] = "";
char parametre[MAX_TOKEN_LEN] = "";
int para_num = 0;
char identifier_arr[MAX_TOKENS][MAX_TOKEN_LEN];
int identifier_num = 0;
int syntax_count;
int ifspecial = 0;



char *index_breakdown(int index_num){
    if(ifspecial == 0){
        char *temp = malloc(MAX_TOKEN_LEN);
        sprintf(temp, "index+%d", index_num);
        return temp;
    }else if(ifspecial == 1){
        char *temp = malloc(MAX_TOKEN_LEN);
        sprintf(temp, "index+size+(%d)", (index_num - syntax_count));
        return temp;
    }else{
        perror("The index cannot be broken down.\n");
        exit(1);
    }
}

void add_special_identifier(int special){
    char temp[MAX_TOKEN_LEN];
    sprintf(temp, "%d", special);
    strcpy(identifier_arr[identifier_num], temp);
    identifier_num++;
}


void syntax_command_check(char *str, int index_num){
    char *type = type_check(str[1]);
    int special = special_type_check(str[2]);
    if(str[0] == '$' && (type != NULL) && str[2] == ':'){
        char *and_op = (strcmp(condition, "") == 0) ? ("        "):("            &&\n        ");
        char temp[MAX_TOKEN_LEN];
        sprintf(temp, "%stype[index+%d] == %s\n", and_op, index_num, type);
        strcat(condition, temp);
        strcpy(temp, "");
        sprintf(temp, "        parametre_list[line_size][%d] = index+%d;\n", para_num, index_num);
        para_num++;
        strcat(parametres, temp);
        slice(str, 3);
        strcpy(identifier_arr[identifier_num], str);
        identifier_num++;
        add_special_identifier(special);
    }
    else if(str[0] == '$' && str[1] == '$' && (special != 0) && str[3] == ':'){
        ifspecial++;
        char *and_op = (strcmp(condition, "") == 0) ? ("        "):("            &&\n        ");
        char temp[MAX_TOKEN_LEN];
        char identifier[MAX_TOKEN_LEN];
        sprintf(temp, "%sexpression(index + %d, size%d)\n", and_op, index_num, (index_num - syntax_count));
        strcat(condition, temp);
        strcpy(temp, "");
        sprintf(temp, "        parametre_list[line_size][%d] = index+%d;\n        parametre_list[line_size][%d] = index+size+(%d);\n", para_num, index_num, para_num+1, (index_num - syntax_count + 1));
        strcat(parametres, temp);
        slice(str, 4);
        strcpy(identifier_arr[identifier_num], str);
        para_num += 2;
        identifier_num++;
        add_special_identifier(special);
    }
    else{
        char *and_op = (strcmp(condition, "") == 0) ? ("        "):("            &&\n        ");
        char *index_variable = index_breakdown(index_num);
        char temp[MAX_TOKEN_LEN];
        sprintf(temp, "%sstrcmp(token[%s], \"%s\") == 0\n", and_op, index_variable, str);
        strcat(condition, temp);
    }
    index_num++;
}

void add_body_in_parse(int fno, int vno, int cno) {
    char string_to_add[FINAL_RESULT_MAX];
    const int line_cursor = 21;
    const char *filename = "../parse/parse.c";
    sprintf(string_to_add, "            case %d:\n                __function_%d_%d__(index, size);\n                break;\n",
        cno,
        vno,
        fno
    );
    // printf("%s", string_to_add);
    write_the_file(filename, string_to_add, line_cursor);
}

void add_body_in_declare_header(int fno, int vno) {
    char string_to_add[FINAL_RESULT_MAX];
    const int line_cursor = 4;
    const char *filename = "../parse/include/declare.h";
    sprintf(string_to_add, "void __function_%d_%d__(int index, int size);\n",
        vno,
        fno
    );
    // printf("%s", string_to_add);
    write_the_file(filename, string_to_add, line_cursor);
}

void add_body_in_declare(int fno, int vno, int cno) {
    char string_to_add[FINAL_RESULT_MAX];
    const int line_cursor = 12;
    const char *filename = "../parse/src/declare.c";
    sprintf(string_to_add, "\nvoid __function_%d_%d__(int index, int size){\n    if(    \n%s    ){\n%s\n        line_method[line_size] = %d;\n        line_size++;\n        found_the_syntax = 1;\n}\n}\n\n",
        vno,
        fno,
        condition,
        parametres,
        cno
    );
    // printf("%s", string_to_add);
    write_the_file(filename, string_to_add, line_cursor);
}


int main() {
    char syntax[200] = "if $$e:a :", program[200] = "if( $$a ) return 0;";
    char *token;
    char token_syntax[MAX_TOKENS][MAX_TOKEN_LEN];
    int type_syntax[MAX_TOKENS];
    char token_program[MAX_TOKENS][MAX_TOKEN_LEN];
    int type_program[MAX_TOKENS];
    int size_syntax = 0;
    int size_program = 0;
    int i = 0, j = 0;

    int cno = 0, vno = 0, fno = 0;
    read_from_file(&vno, &cno);

    // Input syntax string
    // printf("Enter syntax string: ");
    // fgets(syntax, sizeof(syntax), stdin);
    // syntax[strcspn(syntax, "\n")] = '\0';  // Remove newline

    // // Input program string
    // printf("Enter program string: ");
    // fgets(program, sizeof(program), stdin);
    // program[strcspn(program, "\n")] = '\0';  // Remove newline

    // Tokenize syntax string
    syntax_count = count_char(syntax) + 1;
    token = strtok(syntax, " ");
    while (token != NULL && i < MAX_TOKENS) {
        syntax_command_check(token, i);
        strncpy(token_syntax[i], token, MAX_TOKEN_LEN - 1);
        token_syntax[i][MAX_TOKEN_LEN - 1] = '\0'; // Ensure null termination
        i++;
        token = strtok(NULL, " ");
    }
    

    print_string_array(identifier_arr, identifier_num);

    // Tokenize program string
    i = 0;
    token = strtok(program, " ");
    while (token != NULL && i < MAX_TOKENS) {
        program_command_check(token, i);
        strncpy(token_program[i], token, MAX_TOKEN_LEN - 1);
        token_program[i][MAX_TOKEN_LEN - 1] = '\0'; // Ensure null termination
        i++;
        token = strtok(NULL, " ");
    }

    // Output the tokens 
    printf("\nCondition:\n%s", condition);
    printf("\nParametres:\n%s", parametres);
    printf("\nPrompt:\n%s", prompt);
    printf("\nparametre:\n%s", parametre);
    
    // Add the body of function_name in parse.c
    add_body_in_parse(fno, vno, cno);
    
    // Add the function_name in declare.h
    add_body_in_declare_header(fno, vno);
    
    // Add the body of function in declare.c
    // Add the new_function_name in exec.c
    // Add the function body in exec.c
    add_body_in_declare(fno, vno, cno);

    vno++;
    cno++;
    save_to_file(vno, cno);

    return 0;
}
