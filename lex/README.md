# Lexical Analysis

This program functions as a lexer, a fundamental component in compilers and interpreters designed to decompose raw source code into structured units known as tokens. To manage this process, the system utilizes a **Deterministic Finite Automaton (DFA)** model, where the logic formerly handled by character-type tracking and global state variables is now encapsulated within distinct DFA states. The core processing engine, `dfa_char_analysis`, evaluates input character by character to categorize them into token types such as identifiers, keywords, integers, operators, punctuation, and string literals. While specific flags are maintained within `lexInfo` to track structural elements like curly bracket nesting and indentation levels, the transition to a state-machine architecture eliminates the need for a separate character-type structure. The `lexf` function orchestrates the workflow by reading source data and passing it through the DFA transitions, ultimately producing a sequence of tokens ready for the parsing stage without the need for manual EOF token termination checks.


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
