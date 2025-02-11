#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#define MAX 1024



void write_the_file(const char *filename, char *string_to_add, const int line_cursor){
    FILE *fp;
    char line[MAX];
    char res[MAX*MAX];
    int i = 0;
    strcpy(res, "");
    fp = fopen(filename, "r");
    if(fp == NULL){
        printf("Error.\n");
        return;
    }
    while(fgets(line, MAX, fp) != NULL){
        // printf("%s", line);
        if(i == line_cursor){
            strcat(res, string_to_add);
        }
        strcat(res, line);
        i++;
    }
    fclose(fp);
    fp = fopen(filename, "w");
    if(fp == NULL){
        printf("Error.\n");
        return;
    }
    if(fputs(res, fp) == EOF){
        printf("Error putting file.\n");
        fclose(fp);
    }
    fclose(fp);
    return;
} 

void add_body_in_parse(int fno, int vno, int cno){
    char string_to_add[MAX];
    const int line_cursor = 22;
    const char *filename = "../parse/parse.c";
    sprintf(string_to_add, "            case %d:\n                __function_%d_%d__(index, size);\n                break;\n", cno, vno, fno);
    write_the_file(filename, string_to_add, line_cursor);
    return;
}

void add_body_in_declare_header(int fno, int vno){
    char string_to_add[MAX];
    const int line_cursor = 4;
    const char *filename = "../parse/include/declare.h";
    sprintf(string_to_add, "void __function_%d_%d__(int index, int size);\n", vno, fno);
    write_the_file(filename, string_to_add, line_cursor);
}


char *datatype(char token){
    switch(token){
        case 'd':
            return "t_datatype";
        case 'i':
            return "t_identifier";
    }
    return "";
}


void add_body_in_declare(int fno, int vno){
    char string_to_add[MAX];
    const int line_cursor = 4;
    const char *filename = "../parse/src/declare.c";
    char com[MAX];
    char conditions[MAX];
    char statements[MAX];
    char var[MAX][MAX];
    int var_len = 0;
    strcpy(conditions, "");
    strcpy(statements, "");
    scanf("%s", com);
    int i = 0;
    int istype = 0;
    int issyn = 0;
    while(com[i] != '\0'){
        if(com[i] == '$'){
            istype = 1;
        }else if(istype && com[i] == '$'){
            issyn = 1;
            istype = 0;
        }else if(com[i] == ' '){
            istype = 0;
            issyn = 0;
        }else{
            if(istype){
                strcat(conditions, "type[index] == ");
                strcat(conditions, datatype(com[i]));
                strcat(conditions, "\n");
                if(com[i + 1] == ':'){
                    i += 2;
                    int j = 0;
                    char identifier[MAX];
                    while(com[i] != ' '){
                        identifier[j] = com[i];
                        j++;
                        i++;
                    }
                    var[var_len][j] = '\0';
                }
            }else if(issyn){
                // strcat();
            }else{}
        }
        i++;
    }
    sprintf(string_to_add, "void __function_%d_%d__(int index, int size){\n    if(\n", vno, fno);

    write_the_file(filename, string_to_add, line_cursor);
}


int main(){
    int function_num = 0;
    int version_num = 0;
    int case_num = 1;
    // scanf("%d\n%d\n%d", &function_num, &version_num, &case_num);
    // Add the body of function_name in parse.c
    // saveToFile(version_num, case_num);
    readFromFile(&version_num, &case_num);
    add_body_in_parse(function_num, version_num, case_num);
    // Add the function_name in declare.h
    add_body_in_declare_header(function_num, version_num);
    // Add the body of function in declare.c

    // Add the new_function_name in exec.c
    // Add the function body in exec.c
    /*
        if $ is found:
            strcat(new_pgm, token[ parametre[i][num_index] ])
            elif $$expession is found:
            strcat(new_pgm)
    */
    version_num++;
    case_num++;
    saveToFile(version_num, case_num);
    return 0;
}

/*

single $i:id1 = $$expression:exp1;
int $id1 = $$expression:exp1;

*/
