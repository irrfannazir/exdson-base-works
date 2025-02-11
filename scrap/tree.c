#include <stdio.h>
#define MAX 1024

typedef enum{
    t_eof, t_identifier, t_integer, t_keyword,
    //0     1               2           3
    t_op, t_punctuation, t_datatype, t_expression, t_string
    //4     5               6           7           8
} t_type;

int *type = {2, 4, 2, 4, 2};

struct Node{
    int data;
    // 0 : Unary Expression
    // 1 : Binary Exp
    // 2 : Operator
    // 3 : Bracket
    // 4 : Identifier
    // 5 : Function Arguments 
    int start;
    int size;
    struct Node *left;
    struct Node *right;
};

void *createNode(
struct Node *parent, int value, int start, int size, int isright
){
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->start = start;
    newNode->size = size;
    newNode->left = NULL;
    newNode->right = NULL;
    if(isright){
        parent -> right = newNode;
    }else{
        parent -> left = newNode;
    }
    // return newNode;
}

// Function to perform level order traversal and store in an array
int levelOrderTraversal(struct Node* root) {
    int arr[MAX];
    int *index = 0;
    if (root == NULL) return;

    // Create an auxiliary queue for level order traversal
    struct Node* queue[100];  // Assuming a max tree size of 100 for simplicity
    int front = 0, rear = 0;

    // Enqueue root
    queue[rear++] = root;

    while (front < rear) {
        struct Node* current = queue[front++];

        // Add the current node's value to the array
        arr[*index] = current->data;
        printf("%d ", arr[index]);
        (*index)++;

        // Enqueue left and right children if they exist
        if (current->left != NULL) {
            queue[rear++] = current->left;
        }
        if (current->right != NULL) {
            queue[rear++] = current->right;
        }
    }
    return 0;
}

int main(){
    struct Node *root;
    struct Node *ptr;
    ptr -> data = 0;
    ptr -> start = 0;
    ptr -> size = 5;
    createNode(ptr, 1, NULL, NULL, 0);
    createNode(ptr, 2, NULL, NULL, 1);
    ptr = ptr -> left;
    struct Node *backup = ptr;
    createNode(ptr, 0, 0, 1, 0); 
    createNode(ptr, 0, 2, 3, 1); 
    ptr = ptr -> right;
    createNode(ptr, 1, NULL, NULL, 0);
    ptr = root;
    if(levelOrderTraversal(root, ptr)){}
    return 0;
}