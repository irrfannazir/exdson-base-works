# Ex-DSON S2S Compiler

The S2S compiler for LOPS >> language oriented programming system.   
- It dynamically changes the syntax of the program throughout while programming.
- This compiler implements C program with simpler syntax.


### Compiling & Running
1. Write your Ex-c program as input in main.ex file.
   An example program for declaring a variable.
   ```sh
   single a = 3+5*3;
   print{
      "The number is ",
      a,
      "\n"
   }
   ```

2. Run the Main Bat file which includes every compilation commands.
   ```sh
   # In Linux
      bash scripts/linux.bat
   # In Windows
      .\scripts\win.bat
   ```
   OR
   ```sh
   # Run this
   make
   ```
3. It shows the c program which has been executed and shows the details of the compilation.


## Updates

**v2.2.0**
- Added inline functions in method.txt

**v2.1.0**   
- Can compile the program using the compiler which is not MSVC version
- Now we can alter the syntax in order to our will manually or with prompt. You need to install node.js before using prompt.
```sh
# Command to alter the syntax with prompt
node tools/change_method.js
# Command to undo the syntax alteration
node tools/undo_method.js
```



## More about it
Ex-c is a programming language simple programming language syntax to understand the compiler. By analyzing this open-source compiler, you can understand how the common compiler are working. 

*The Ex-DSON Compiler is lightwieght.*  
The syntax is primitive. So, it is simple and lightwieght.

1. To activate interactive mode, Just type "ex-c".
2. To update the compiler with new syntax format. 

## Implementation
The compiler has implemented by splitting the execution into three operations.
1. Lexical Analysis (src/lexer) - Analyses and split the tokens from the input command or program
2. Parsing Algorithm (src/parser) - Analyses the tokens via AST
3. Compilation Process (src/compiler) - Compiles the parsed information to c program
4. Core Functiosn (src/core) - It is for commonly used functions.