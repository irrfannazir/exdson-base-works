#ifndef TREE_NODE_H
#define TREE_NODE_H
#define UNARY_EXPRESSION 0
#define BINARY_EXPRESSION 1
#define OPERATOR 2
#define BRACKET 3
#define IDENTIFIER 4
#define FUNCTION_ARGUMENTS 5

struct Node{
    int data; // Assign the macro value to this variable
    int start;
    int size;
    struct Node *left;
    struct Node *right;
};

struct Node *find_next_expression(struct Node* root);
void *createNode(int value, int start, int size);
void display_postfix_reversed(struct Node *ptr);
void display_postfix(struct Node *ptr);
void save_expression_root(struct Node *root);
int isVariableDeclared(int index);

extern struct Node *root_array[500];

#endif