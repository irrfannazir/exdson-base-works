#ifndef SYNTAX_COMMENT_H
#define SYNTAX_COMMENT_H

static inline int is_inline_comment(const char *str){
    if(!str) return 0;
    return str[0] == '/' && str[1] == '/';
}

static inline int is_inline_function(const char *str){
    if(!str) return 0;
    return str[0] == '$' && str[1] == '$';
}

int contains_function(const char *str);

#define SYNTAX_COMMENT_TOKEN "//"
#define SYNTAX_FUNCTION_TOKEN "$$"


#endif