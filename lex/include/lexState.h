#ifndef LEXSTATE_H
#define LEXSTATE_H

struct lexState {
    int isstring;
    int isenter;
    int isspacef;
    int iscurly;
};

static inline struct lexState initLexState() {
    struct lexState state;
    state.isstring = 0;
    state.isenter = 0;
    state.isspacef = 0;
    state.iscurly = 0;
    return state;
}

#endif