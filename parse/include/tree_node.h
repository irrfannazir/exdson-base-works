#ifndef TREE_NODE_H
#define TREE_NODE_H
// #define NULL 0

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

struct Node *find_the_exp(struct Node* root);
void *createNode(int value, int start, int size);
void display_postfix_reversed(struct Node *ptr);
void display_postfix(struct Node *ptr);
void add_the_root(struct Node *root);

extern struct Node *root_array[500];

#endif