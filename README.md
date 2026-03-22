# Ex-DSON S2S Compiler

The S2S compiler for LOPS >> language oriented programming system.   
- It dynamically changes the syntax of the program throughout while programming.
- This compiler implements C program with simpler syntax.

## Application

- Robotics: A new simple programming language can be created for robot mechanism, instead of programming multiple lines at once
- Software Development: Organize multiple programs as a customized syntax.


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


*Complexity and efficiency*
Consider n as the number of tokens in the program, m as the maximum length of the string, referred in the program header file.
**TIME COMPLEXITY: Omega(n)**
**SPACE COMPLEXITY: O(m)**

## Installation
1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/exdson-base-works.git
   cd exdson-base-works
   ```
2. Run the compiler:
   ```sh
   ./main.exe
   ```

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
      bash linux.bat
   # In Windows
      .\win.bat
   ```
3. It shows the c program which has been executed and shows the details of the compilation.


## Features
1. To activate interactive mode, Just type "ex-c".
2. To update the compiler with new syntax format. 

## Implementation
The compiler has implemented by splitting the execution into three operations.
1. Lexical Analysis (/lex) - Analyses and split the tokens from the input command or program
2. Parsing Algorithm (/alt-parse) - Analyses the tokens via AST
3. Compilation Process (/alt-compile) - Compiles the parsed information to c program
