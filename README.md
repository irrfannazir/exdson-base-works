#Ex Playground

Some have noticed the S2S compiler i made. I think now it's time to play with it.

*How can i use it?*
Run this for interactive mode.
```sh
./ex-c
```
Run this for compile a file.
```sh
./ex-c main.ex
```


## Instructions
1. You can run .js files in tools folder.   
*To change the syntax of the programming language with prompts you give*
```sh
node tools/change_method.js
```
*To undo it.*
```sh
node tools/undo_method.js
```
There are some c programs. You should be careful to handle them.
2. You should be careful while handling file in "parse/grammar/method.txt".
>> If you want to comment anything in text file, just start with '//'. If '//' is in the line but not at first, then after '//' is a text which shows when the syntax in line detected.
>> Dont change the following token in text file present in text file.
    TOKEN_DATATYPE, TOKEN_ID, EXPRESSION, TOKEN_INTEGER, FUNCTION_NAME
>> The compiler saves the token from user whenever the token in text file starting with TOKEN is found. The compiler saves the starting token and ending token from user whenever the token which does not start with TOKEN in text file with capital letter (like EXPRESSION).
If the order of the saving does changed just remember it. Answer it when i ask it later. Not now
>> Dont change the line by line order of the syntax. 
>> Only write in english characters. Even if it is another language.
