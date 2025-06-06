echo This is command to compile the compiler.
gcc main.c data.c ^
    lex/lex.c lex/src/indent.c lex/src/token.c lex/src/character.c lex/src/keyword.c ^
        lex/src/type.c                                                               ^
    parse/parse.c parse/src/print.c parse/src/buffer.c parse/src/declare.c parse/src/condition.c ^
        parse/src/exio.c parse/src/tree.c parse/src/tree_node.c parse/src/tree_least_priority.c  ^
        parse/src/expression.c parse/tests/analyzer.c parse/src/split.c                          ^
    compile-c/compile.c compile-c/src/exec.c compile-c/src/basic.c compile-c/src/declaration.c ^
        compile-c/src/print.c compile-c/src/if.c compile-c/src/write.c compile-c/src/cursor.c  ^
    -I lex -I parse -I compile -I lex/include -I parse/include -I parse/tests -I compile-asm/include -I compile-asm/tests -o main
.\main