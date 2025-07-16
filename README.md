# Ex-DSON Transpiler

I have seen lots of people who have been working hard on labs and studying programming langs. This transpiler implements C program with simpler syntax ever. Here's the transpiler built for student who are working hard on c programming language.


## Overview
Ex-DSON (Excelon DSON) is a programming language simple programming language syntax to understand the compiler. By analyzing this open-source compiler, you can understand how the common compiler are working. 


*How it's working?*  
This Transpiler translates the programming language written inside the compiler program into C, compiles it.

*The Ex-DSON transpiler is lightwieght.*  
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
1. Write your Exdson program as input in main.ex file.
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
      bash com.bat
   # In Windows
      ./com.bat
   ```
3. It shows the c program which has been executed and shows the details of the compilation.


## Features
1. To activate interactive mode. Remove the comment of (#define READ_FROM_INPUT) in dependencies.h.
2. To update the compiler with new syntax format. Run
   ```sh
   # In Linux
      bash update.bat
   # In Windows.
      ./update.bat
   ```
   Then enter the syntax and the syntax to implement in c.

