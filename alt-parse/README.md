# Parsing Algorithm

This program is part of a parser, the stage of a compiler or interpreter that
comes after lexing. While the lexer is responsible for decomposing raw source text into discrete tokens, this parser evaluates those tokens against predefined grammatical rules. Its primary objective is to validate the program’s syntax. 

The execution begins within the **parsef** function. Two primary counters: `method_line_num` and `method_token_num`, track the current position within the grammar rules. The engine iterates until every token from the program has been successfully evaluated with the method.


The Algorithm:
```sh
FUNCTION parsef(src_filename, dest_filename):
    
    INITIALIZE output files (dest_filename and identifier storage)
    
    SET method_line_num = 0
    SET method_token_num = 0
    
    LOOP indefinitely:
        
        // Fetchs current rule and current token index from lex
        word = get_word_from_method(method_line_num, method_token_num)
        index = get_index_from_lex(current_offset = 1)
        current_token = get_token(index)


        // Handle End of Line / End of File
        IF current_token is NULL AND word is NULL:
            SKIP_TO_NEXT_LINE(method_line_num, method_token_num)
            
            // Check if more tokens exist at the start of the new line
            IF get_token(get_index_from_lex(0)) is NULL:
                LOG_DEBUG "End of parsing"
                RETURN
            ELSE:
                CONTINUE loop

        // Handle missing data or invalid indices
        IF index is -1 OR word is NULL:
            IF handle_missing_word_or_token(word, index, method_line_num, method_token_num):
                CONTINUE loop
            ELSE:
                SKIP_TO_NEXT_METHOD(method_line_num, method_token_num)
                CONTINUE loop

        // Handle errors specifically at the start of a method
        IF word is NULL AND (index is -1 OR method_token_num is 0):
            REPORT_METHOD_ERROR(method_line_num)
            SET dont_compile = 1
            IF SKIP_TO_NEXT_LINE(method_line_num, method_token_num):
                BREAK loop (End of File)
            CONTINUE loop

        // Save Identifier Context
        // (Used for tracking declarations before matching)
        handle_identifier_declaration(index, method_line_num)

        // Match by Type (e.g., INT_LITERAL, IDENTIFIER)
        IF try_match_type(word, index, method_token_num):
            CONTINUE loop

        // Match by Exact Word (e.g., "if", "while", "{")
        IF try_match_word(word, index, method_token_num):
            CONTINUE loop

        // Structural Analysis (Syntax Trees)
        IF does_tree_needed(word):
            IF handle_syntax_tree(word, index, method_line_num, method_token_num):
                CONTINUE loop
        ELSE:
            // No match found in this method path, try the next alternative
            LOG_DEBUG "Not this syntax"
            SKIP_TO_NEXT_METHOD(method_line_num, method_token_num)
    END LOOP
END FUNCTION
```

The engine have a weak error checking system.