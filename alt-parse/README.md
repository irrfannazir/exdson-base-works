# Parsing Algorithm

This program is part of a parser, the stage of a compiler or interpreter that
comes after lexing. While the lexer breaks raw text into tokens, the parser
tries to match those tokens against grammatical rules to ensure the program’s
syntax is valid and to prepare for further compilation or interpretation.


Here’s what happens:
The file starts by including headers for data handling, parser utilities, debugging,
and error reporting. It defines a default error message "Invalid Syntax" and a
global flag isparsing to keep track of parsing state. The main function, parsef,
begins by printing a message and initializing the parser with create_the_parser_file().
It then sets up two counters, mln and mtn, which represent the current method line
number and token number inside that method. The parser enters an infinite loop that
continues until all tokens have been processed.

Inside the loop, the parser retrieves the next expected word from the parsing rules
(get_word_from_method) and the current token index from the lexer
(get_index_from_lex). It then compares the parsing rule with the actual token.

Depending on the situation, several cases occur:

1. If both the word and token are NULL, it moves to the next line, possibly ending
parsing if no tokens remain.
2. If the word is NULL but tokens remain, it raises an error, skips the line, and
continues.
3. If tokens don’t match the expected word, it tries the next parsing method.
4. If the expected word matches either by type (check_the_type) or exact spelling
(compare_the_word), the parser consumes the token (next_token).
5. If a syntax tree is needed (does_tree_needed), the parser collects a range of
tokens, pushes them into a parse buffer, and calls parsing_tree_analysis to analyze
that fragment of syntax.
6. Otherwise, if nothing matches, it skips ahead to try another parsing method.

At every stage, errors are handled: if unexpected or missing tokens are found,
error messages are printed using either the parser’s own method error messages
or the default syntax error message. The loop continues until all tokens are
processed or the end of the file is reached. Debugging information (guarded
by P_PARSE_DEBUG_MODE) can print detailed traces of the parser’s decisions.
