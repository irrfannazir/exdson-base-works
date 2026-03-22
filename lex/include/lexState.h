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
    int current_token_length;
    const char *lhfn;
};

static inline struct lexState initLexState(const char *dest_filename) {
    struct lexState state;
    state.isstring = 0;
    state.isenter = 0;
    state.isspacef = 0;
    state.iscurly = 0;
    state.prev = CTYPE_PUNCT;
    state.space_count = 0;
    state.current_token_length = 0;
    state.lhfn = dest_filename;
    return state;
}

#endif