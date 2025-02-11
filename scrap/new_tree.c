#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "tree.h"


typedef enum{
    t_eof, t_identifier, t_integer, t_keyword,
    //0     1               2           3
    t_op, t_punctuation, t_datatype, t_expression, t_string
    //4     5               6           7           8
} t_type;

int type[MAX] = {2, 4, 2, 4, 2};
char *token[MAX] = {"2", "+", "3", "*", "5"};

char *function_id[500] = {"func"};
int function_len[500] = {1};
int function_size = 1;


// struct Node{
//     int data;
//     // 0 : Unary Expression
//     // 1 : Binary Exp
//     // 2 : Operator
//     // 3 : Bracket
//     // 4 : Identifier
//     // 5 : Function Arguments 
//     int start;
//     int size;
//     struct Node *left;
//     struct Node *right;
// };

int isfunction(struct Node *ptr){
    for(int i = 0; i < function_size; i++){
        if(
            strcmp(token[ptr -> start], function_id[i]) == 0
                &&
            strcmp(token[ptr -> start + 1], "(") == 0
                &&
            strcmp(token[ptr -> start + ptr -> size - 1], ")") == 0
        ){
            return i;
        }
    }
    return -1;
}

void *createNode(int value, int start, int size){
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->start = start;
    newNode->size = size;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

int find_the_least_priority(int start, int size){
    int bracket_is_opened = 0;
    int index = -1;
    int priority = -1;
    int i = start;
    printf("%d:%d\n", start, size);
    while(i < start + size){
        printf("\n%s\n", token[i]);
        if(strcmp(token[i], "(") == 0){
            bracket_is_opened = 1;
        }else if(strcmp(token[i], ")") == 0){
            bracket_is_opened = 0;
        }else if(bracket_is_opened == 0){
            if(strcmp(token[i], "/") == 0 && priority < 0){
                index = i;
                priority = 0;
            }else if(strcmp(token[i], "*") == 0 && priority < 1){
                index = i;
                priority = 1;
            }else if(strcmp(token[i], "+") == 0 && priority < 2){
                index = i;
                priority = 2;
            }else if(strcmp(token[i], "-") == 0 && priority < 3){
                index = i;
                priority = 3;
            }
        }
        i++;
    }
    return index;
}

int count(char *str, struct Node *ptr) {
    int count = 0;

    // Iterate from the 'start' index and check 'size' elements
    for (int i = ptr -> start; i < ptr -> start + ptr -> size && i < sizeof(token) / sizeof(token[0]); i++) {
        if (strcmp(str, token[i]) == 0) {
            count++;
        }
    }

    return count;
}

// Function to perform level order traversal and store in an array
struct Node *find_the_exp(struct Node* root) {
    int arr[MAX];
    int index = 0;
    if (root == NULL) return NULL;
    if (root -> data == 0 && root -> size > 1 && root -> right == NULL && root -> left == NULL) return root;

    // Create an auxiliary queue for level order traversal
    struct Node* queue[100];  // Assuming a max tree size of 100 for simplicity
    int front = 0, rear = 0;

    // Enqueue root
    queue[rear++] = root;
    while (front < rear) {
        struct Node* current = queue[front++];

        // Add the current node's value to the array
        arr[index] = current->data;
        // printf("$d");

        if(current -> data == 0 && current -> size > 1 && current -> right == NULL && current -> left == NULL
        ){
            return current;
        }
        (index)++;

        // Enqueue left and right children if they exist
        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
    printf("Finished the program.\n");
    return NULL;
}

void exp_analysing(struct Node *root){
    struct Node *ptr = find_the_exp(root);
    int j = 0;
    printf("%d", ptr != NULL);
    while(ptr != NULL){
        printf("k");
        int a = find_the_least_priority(ptr -> start, ptr -> size);
        if(a != -1){
            ptr -> right = createNode(2, a, -1);
            //Operator
            ptr -> left = createNode(1, -1, -1);
            // Binary
            ptr -> left -> right = createNode(0, ptr -> start, a - ptr -> start);
            ptr -> left -> left = createNode(0, a + 1, ptr -> size + ptr -> start - a - 1);
            printf(":: %d\n", ptr -> start - a + ptr -> size);
            ptr = ptr -> left;
        }else if(isfunction(ptr) != -1){
            ptr -> right = createNode(5, ptr -> start, 1);
            struct Node *ptr2 = ptr;
            int count = 0;
            int comma_found[MAX];
            int end = ptr2 -> start + ptr2 -> size - 1;
            for (int i = ptr -> start + 2; i < ptr -> start + ptr -> size && i < sizeof(token) / sizeof(token[0]); i++) {
                if (strcmp(",", token[i]) == 0) {
                    comma_found[count] = i;
                    count++;
                }
            }
            ptr2 -> right = createNode(5, ptr -> start, 1);
            while(count > 0){
                ptr2 -> left = createNode(5, -1, -1);
                ptr2 = ptr2 -> left;
                count--;
                ptr2 = ptr2 -> left;
                ptr2 -> right = createNode(0, comma_found[count], end - comma_found[count]);
                end = comma_found[count];
            }
            ptr2 -> left = createNode(0, ptr2 -> start + ptr2 -> size + 2, end);
        }else{
            printf("invalid expression.\n");
            return;
        }
        ptr = find_the_exp(ptr);
        j++;
        // printLeafNodes(root);
    }
}

void levelOrderTraversal(struct Node* root) {
    int arr[MAX];
    int index = 0;
    if (root == NULL) return;

    // Create an auxiliary queue for level order traversal
    struct Node* queue[100];  // Assuming a max tree size of 100 for simplicity
    int front = 0, rear = 0;

    // Enqueue root
    queue[rear++] = root;

    while (front < rear) {
        struct Node* current = queue[front++];

        // Add the current node's value to the array
        arr[index] = current->data;
        printf("\n%d: %d: %d: %p: %p in %p\n", current ->data, current ->start, current -> size, current -> left, current -> right, current);
        (index)++;

        // Enqueue left and right children if they exist
        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
    // return 0;
}


int main(){
    struct Node *root = createNode(0, 0, 5);
    // root -> left = createNode(0, 0, 1);
    // root -> right = createNode(0, 3, 2);
    exp_analysing(root);
    printf("e");
    levelOrderTraversal(root);
    printLeafNodes(root);
    printf("\n%d\n", find_the_exp(root));
}
