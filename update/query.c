#include <stdio.h>
#include <string.h>
#include "file.h"

void analyse_the_query(char *conditions, char *parametres){
    char syntax[MAX];
    int i = 0;
    int istype = 0;
    int issyn = 0;
    int index_num = 0;
    int para_num = 0;
    char comparing[MAX];
    int comp_len = 0;
    char temp[MAX];
    char input[MAX];
    //For syn
    scanf("%[^\n]s", syntax);
    while(syntax[i] != '\0'){
        if(syntax[i] == '$'){
            istype = 1;
        }else if(istype && syntax[i] == '$'){
            issyn = 1;
            istype = 0;
        }else if(syntax[i] == ' '){
            if(comp_len != 0){
                do_compare_the_str(comparing, conditions, index_num);
            }
            index_num++;
        }else{
            if(istype){
                // Type checking and saving
                i = do_find_the_type(syntax, i, conditions, parametres, index_num, para_num);
                para_num++;
                istype = 0;
                issyn = 0;
            }else if(issyn){
                // Syntax cheching and saving
                istype = 0;
                issyn = 0;
            }else{
                //Comparing
                comparing[comp_len] = syntax[i];
                comp_len++;
            }
        }
        i++;
    }
    
    sprintf(temp,         "        parametre_list[line_size][%d] = -1;",  para_num);
    strcat(parametres, temp);
}