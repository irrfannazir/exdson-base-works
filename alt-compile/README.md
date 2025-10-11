# Compilation process

This program represents the compiler stage of a custom programming language
pipeline. After the lexer and parser have converted source code into a structured
form, this stage interprets that structure and generates equivalent C code, which
is then compiled and executed.

The main idea is that each parsed line of the custom language is translated into
an action. The function process_parametres decides what kind of statement is being
handled based on a numeric code stored in the parsed line (for example, 0 means a
declaration, 2 means an if block, 5 means a for loop, 7 means a print statement).
Depending on the case, it calls specialized functions (declaration_exec,
block_paradigm, else_condition, etc.) to produce the proper C code.

The function add_the_program reads the parsed program line by line from an
intermediate file created by the parser. It trims and converts each line into
an integer array that represents tokens or instructions. Each line is then passed
through process_parametres, which adds the appropriate translated code to the output
C program. It also keeps track of indentation levels to correctly handle nested
blocks, ensuring that control structures like if or while are properly opened and
closed.

Finally, the function compilef orchestrates the compilation. If errors have been
detected earlier (dont_compile flag), it stops. Otherwise, it creates a fresh C
output file, calls add_the_program to fill it with translated C code, and then
cleans up extra placeholders (such as markers for program, function, and include
sections). After that, it prints the generated C program for inspection and calls
compile_file to invoke a real C compiler on the output.

In theory, this stage acts as a code generator and compiler driver: it transforms
high-level constructs of the custom language into equivalent C constructs, organizes
them into a valid C program, and then compiles that program into an executable. In
a typical compiler pipeline, this corresponds to the code generation and compilation
phase, bridging the gap between abstract parsed structures and runnable machine
code.
