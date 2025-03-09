#include <stdio.h>
#include <string.h>
#include "file.h"


void analyse_the_input(int cno){
    char string_to_add[FINAL_RESULT_MAX];
    const int line_cursor = 44;
    const char *filename = "../compile-c/src/exec.c";
    char input[MAX];
    char syntax[MAX];
    char add_para[MAX];
    int syn_len = 0;
    int istype = 0;
    int issyn = 0;
    int i = 0;
    strcpy(add_para, "");
    printf("Enter the input: ");
    scanf("\n%[^\n]s", input);
    while(input[i] != '\0'){
        if(input[i] == '$'){
            istype = 1;
        }else if(istype && input[i] == '$'){
            issyn = 1;
            istype = 0;
        }else if(input[i] == ' '){
            istype = 0;
            issyn = 0;
            syntax[syn_len] = ' ';
            syn_len++;
        }else{
            if(istype){
                int index_var;
                char temp_var[MAX] = "";
                int temp_len = 0;
                while(input[i] != ' ' && input[i] != ';' && input[i] != '\0'){
                    temp_var[temp_len] = input[i];
                    i++;
                    temp_len++;
                }
                temp_var[temp_len] = '\0';
                syntax[syn_len] = '%';
                syn_len++;
                syntax[syn_len] = 's';
                syn_len++;
                syntax[syn_len] = input[i];
                syn_len++;
                index_var = check_var(temp_var);
                if(index_var != -1){
                    char temp_char[MAX] = "";
                    sprintf(temp_char, ", token[parametre_list[i][%d]]", index_var);
                    strcat(add_para, temp_char);
                }else{
                    printf("not found : %s\n", temp_var);
                    return;
                }
                istype = 0;
            }else if(issyn){
                while(input[i] != ' '){
                    i++;
                }
                syntax[syn_len] = '%';
                syn_len++;
                syntax[syn_len] = 's';
                syn_len++;
                issyn = 0;
            }else{
                syntax[syn_len] = input[i];
                syn_len++;
            }
        }
        i++;
    }
    syntax[syn_len] = '\0';
    sprintf(string_to_add, "            case %d:\n                sprintf(temp, \"%s\"%s);\n                pgm = append_at_index(pgm, temp, pgm_cursor);\n                break;\n", cno, syntax, add_para);
    // printf("%s", string_to_add);
    write_the_file(filename, string_to_add, line_cursor);
}