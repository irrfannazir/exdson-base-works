typedef enum{
    EXPRESSION,         // 0
    OPERATOR,           // 1
    BINARY_EXPRESSION,  // 2
    TERT_EXPRESSION,    // 3
} NodeType;

struct Node{
    NodeType type;
    int start;
    int size;
    char *format;
    struct Node *left;
    struct Node *right;
};
