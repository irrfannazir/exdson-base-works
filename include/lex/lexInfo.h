#ifndef LEXINFO_H
#define LEXINFO_H

struct lexInfo {
    int indent;
    int ignore_newline;
    int point;
};

static inline struct lexInfo init_lexInfo() {
    struct lexInfo li;
    li.indent = 0;
    li.ignore_newline = 0; 
    li.point = 0;
    return li;
}

#endif