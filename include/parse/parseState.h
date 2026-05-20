#ifndef PARSESTATE_H
#define PARSESTATE_H

#define BUFFER_MAX 1024

struct parseState{
    int method_line_number;
    int method_token_number;
    int reg_avail;
    char buffer[BUFFER_MAX];
};

static inline struct parseState init_parseState(){
    struct parseState ps;
    ps.method_line_number= 0;
    ps.method_token_number = 0;
    ps.reg_avail = 0;
    strcpy(ps.buffer, "");
    return ps;
}

#endif