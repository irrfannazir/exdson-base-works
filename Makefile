CC = gcc
CFLAGS = -Wall\
         -I lex -I alt-parse -I alt-compile \
         -I lex/include -I alt-parse/include -I alt-compile/include

SRC = main.c data.c src/get.c src/dir.c src/flush.c \
    lex/lex.c lex/src/indent.c lex/src/token.c lex/src/character.c lex/src/check.c \
    lex/src/type.c lex/src/appendf.c lex/src/readf.c lex/src/d_add.c \
    alt-parse/parse.c alt-parse/src/word.c alt-parse/src/next.c alt-parse/src/type.c \
    alt-parse/src/error.c alt-parse/src/compare.c alt-parse/src/comment.c \
    alt-parse/src/tree_check.c alt-parse/src/push.c alt-parse/src/tree.c \
    alt-parse/src/node.c alt-parse/src/analyze.c alt-parse/src/expression.c \
    alt-parse/src/line.c alt-parse/src/tokenize.c alt-parse/src/command.c \
    alt-compile/compile.c alt-compile/src/cfh.c alt-compile/src/datatype.c \
    alt-compile/src/findfh.c alt-compile/src/insertfh.c alt-compile/src/pfh.c \
    alt-compile/src/remove.c alt-compile/src/s_block.c alt-compile/src/s_decl.c \
    alt-compile/src/s_for.c alt-compile/src/scanl.c alt-compile/src/serialize.c \
    alt-compile/src/s_print.c

OBJ = $(SRC:.c=.o)

TARGET = main

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	del /s /q *.o
