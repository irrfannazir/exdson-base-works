#ifndef LEXSTATE_H
#define LEXSTATE_H

// The c_type is to store the type of previous character
typedef enum{
    CTYPE_CHAR,      // a-z, A-Z
    CTYPE_DIGIT,     // 0-9
    CTYPE_PUNCT,     // punctuation like ; , ( )
    CTYPE_OPERATOR   // + - * / = etc.
} c_type;

struct lexState {
    int isstring;
    int isenter;
    int isspacef;
    int iscurly;
    c_type prev;
    int space_count;
};

static inline struct lexState initLexState() {
    struct lexState state;
    state.isstring = 0;
    state.isenter = 0;
    state.isspacef = 0;
    state.iscurly = 0;
    state.space_count = 0;
    return state;
}

#endif