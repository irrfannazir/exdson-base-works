echo This is command to compile or install the compiler.
@REM xargs npm install < packages.txt
gcc main.c data.c src/* lex/lex.c lex/src/* alt-parse/parse.c alt-parse/src/* alt-compile/compile.c alt-compile/src/* fileh/src/* ^
    -I lex -I alt-parse -I alt-compile -I lex/include -I alt-parse/include -I alt-compile/include -I fileh/include -o ex-c
.\ex-c main.ex