//Checks whether it is a character
int is_char(char c){
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')){
        return 1;
    }
    return 0;
}

//Checks whether it is a digit
int is_digit(char c){
    if(c >= '0' && c <= '9'){
        return 1;
    }
    return 0;
}

//Checks whether it is a punctuator
int is_punct(char c){
    const char *punct = "(){}[].,:'\"";
    for(int i = 0; punct[i] != '\0'; i++){
        if(punct[i] == c){
            return 1;
        }
    }
    return 0;
}

//Checks whether it is an operator
int is_oper(char c){
    const char *operators = "+-*/=<>";
    for(int i = 0; operators[i] != '\0'; i++){
        if(operators[i] == c){
            return 1;
        }
    }
    return 0;
}
