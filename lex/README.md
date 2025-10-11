# Lexical Analysis

This program is part of a lexer (lexical analyzer), a tool used in compilers and
interpreters to break down raw source code into meaningful units called tokens. 
It defines two main enums: c_type, which tracks the type of the previously processed
character (letter, digit, punctuation, or operator), and t_type, which represents 
different token categories such as identifiers, integers, keywords, operators,
punctuation, datatypes, expressions, and string literals. Several global variables
are used to manage lexer state, such as whether the lexer is inside a string, handling
whitespace, or inside curly braces. The core function, char_analysis, processes one
character at a time: if it encounters letters, it groups them into identifiers; digits
into integer tokens; operators like + or - into operator tokens; punctuation like (, )
or ; into punctuation tokens; and quoted sequences into string tokens. It also checks
for errors when encountering unknown characters. The lexf function orchestrates the
process: it either reads user input or loads a file, then passes each character through
char_analysis. At the end, it ensures the token stream is properly terminated with an
EOF token. Overall, the program scans source code and converts it into a sequence of
structured tokens that later compiler stages (like parsing) can use.
