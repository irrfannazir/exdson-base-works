#include <stdio.h>
#include "tree.h"
#include "../data.h"
#include "pdebug.h"


/*It is the where parsing tree in implemented*/

int parsing_tree_analysis(char *format, int start, int size){
    struct Node *root = createNode(format, EXPRESSION, start, size);
    struct Node *ptr = find_next_expression(root);
    int endloop = 0;
    while(ptr != NULL && endloop < 20){
        #ifdef P_TREE_MODE
         printf("from %s", get_token(ptr -> start));
         printf("to %s\n", get_token(ptr -> start + ptr -> size));
        #endif
        int status = analyze_expression(ptr);
        if(status){
            printf("Invalid Expression.\n");
            return 1;
        }
        ptr = find_next_expression(root);
        endloop++;
    }
    return 0;
}
