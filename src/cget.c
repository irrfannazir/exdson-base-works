#include "fileh.h"
#include "../alt-parse/include/strh.h"

char *get_nth_line(const char* filename, int n, const char *keyword){
    
        FILE* file = fopen(filename, "r");
        if (!file) return NULL;

        const int size = sizeof(char) * 256;
        char *line = malloc(size);

        if(keyword != NULL){
            while(fgets(line, size, file)){
                int line_len = strlen(line);
                if(line[line_len - 1] == '\n' && line[line_len - 2] == ':'){
                    line[line_len - 2] = '\0'; 
                }else if(line[line_len - 1] == '\n'){
                    line[line_len - 1] = '\0'; 
                }
                if(strcmp(line, keyword) == 0){
                    // printf("Checking keyword %s and %s\n", line, keyword);
                    break;
                }
            }
        }


        while (n) {
            if( fgets(line, size, file) ){
                n--;
            }else{
                fclose(file);
                return NULL;
            }
        }
        fclose(file);
        return line;
}

// char* get_nth_line(const char* filename, int n, const char *keyword, int countcolon) {
//     if (!file_exists(filename)) return NULL;

//     FILE* file = fopen(filename, "r");
//     if (!file) return NULL;

//     char* line = NULL;
//     size_t len = 0;
//     ssize_t read;
//     int current_line = 0;
//     char* result = NULL;
//     if(keyword != NULL){
//         while((read = getline(&line, &len, file)) != -1){
//             int line_len = strlen(line);
//             if(line[line_len - 1] == '\n' && line[line_len - 2] == ':'){
//                 line[line_len - 2] = '\0'; 
//             }else if(line[line_len - 1] == '\n'){
//                 line[line_len - 1] = '\0'; 
//             }
//             if(strcmp(line, keyword) == 0){
//                 // printf("Checking keyword %s and %s\n", line, keyword);
//                 break;
//             }
//         }
//     }

//     while ((read = getline(&line, &len, file)) != -1) {
//         if (current_line == n) {
//             result = strdup(line);
//             break;
//         }
//         if(countcolon){
//             int line_len = strlen(line);
//             if(line[line_len - 2] == ':'){
//                 current_line++;
//             }
//             if(current_line == n){
//                 line[line_len - 2] = '\0';
//                 result = strdup(line);
//                 return result;
//             }
//         }else{
//             current_line++;
//         }
//     }

//     free(line);
//     fclose(file);
//     return result;
// }