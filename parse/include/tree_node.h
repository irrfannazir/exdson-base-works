#ifndef TREEF_H
#define TREEF_H
#define UNARY_EXPRESSION 0
#define BINARY_EXPRESSION 1
#define OPERATOR 2
#define BRACKET 3
#define IDENTIFIER 4
#define FUNCTION_ARGUMENTS 5
#include "node.h"

extern struct Node *root_array[500];

struct Node *find_next_expression(struct Node* root);
void *createNode(int value, int start, int size);
void save_expression_root(struct Node *root);
int find_the_unary(int index, int size);


#endif