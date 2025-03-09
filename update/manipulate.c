#include <stdio.h>
#include <string.h>
#include "file.h"

int do_find_the_type(char *syntax, int i, char *conditions, char *parametres, int index_num, int para_num){
    char temp_cond[MAX];
    char temp_para[MAX];
    int flag = 0;
    if(isand){
        sprintf(temp_cond, "            &&\n        type[index+%d] == %s\n", index_num, datatype(syntax[i]));
    }else{
        sprintf(temp_cond, "        type[index+%d] == %s\n", index_num, datatype(syntax[i]));
    }
    isand = 1;
    strcat(conditions, temp_cond);
    sprintf(temp_para, "        parametre_list[line_size][%d] = index+%d;\n", para_num, index_num);
    strcat(parametres, temp_para);
    if(syntax[i + 1] == ':'){
        char identifier[MAX];
        int j = 0;
        int break_flag = 0;
        i += 2;
        while(syntax[i] != ' ' && syntax[i] != ';'){
            identifier[j] = syntax[i];
            i++;
            // $d:num1 $d:num2 $d:num3;
            j++;
        }
        i--;
        identifier[j] = '\0';
        strcpy(var[var_len], identifier);
        var_index[var_len] = index_num;
        var_len++;
    }
    return i;
}

void do_compare_the_str(char *comp, char *cond, int index_num){
    char temp[MAX];
    // printf("i ");
    if(isand){
        sprintf(temp, "            &&\n        strcat(token[index+%d], \"%s\") == 0\n", index_num, comp);
    }else{
        sprintf(temp, "        strcat(token[index+%d], \"%s\") == 0\n", index_num, comp);
    }
    strcat(cond, temp);
    return;
}