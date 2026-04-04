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



Edit the functions:
    void append(char c, int *current_token_length)
    void new_token(char c, int *current_token_length)


Algorithm: DFA
    case 0 (Start State)
        If QUOTE:
            new_token()
            next_type(STRING)
            state ← S4

        Else if LETTER:
            new_token(c)
            next_type(IDENTIFIER)
            state ← S1

        Else if DIGIT:
            new_token(c)
            next_type(INTEGER)
            state ← S2

        Else if OPERATOR:
            new_token(c)
            next_type(OPERATOR)
            state ← S3

        Else if PUNCT:
            new_token(c)
            next_type(PUNCTUATION)
            state ← S7

        Else if SPACE:
            handle whitespace
            state ← S5

        Else if NEWLINE:
            handle newline
            state ← S6

        Else:
            report error
            state ← SERR
    case 1 (Identifier State)
        If LETTER or DIGIT:
            append(c)

        Else:
            finalize token
            state ← S0
            reprocess current character

    case 2 (Integer State)
        If DIGIT:
            append(c)

        Else if DOT:
            append(c)   // floating support

        Else:
            finalize token
            state ← S0
            reprocess current character
    case 3 (Operator State)
        If OPERATOR:
            append(c)

        Else:
            finalize token
            state ← S0
            reprocess current character
    case 4 (String State)
        If QUOTE:
            finalize token
            state ← S0

        Else:
            append(c)
    case 5 (Whitespace State)
        If SPACE:
            continue

        Else:
            if previous was not space:
                finalize token
            state ← S0
    reprocess current character
    case 6 (Newline State)
        If inside curly braces:
            ignore newline

        Else:
            finalize token
            emit EOF token
            call newline()

        state ← S0
    case 7 (Punctuation State)
        finalize token
        state ← S0
    case 8 (Error State)
        print error message
        recover (optional)
        state ← S0
