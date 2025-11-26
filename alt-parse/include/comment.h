#ifndef SYNTAX_COMMENT_H
#define SYNTAX_COMMENT_H

static inline int is_inline_comment(const char *str){
    return str[0] == '/' && str[1] == '/';
}

static inline int is_inline_function(const char *str){
    return str[0] == '$' && str[1] == '$';
}


#define SYNTAX_COMMENT_TOKEN "//"

#endif