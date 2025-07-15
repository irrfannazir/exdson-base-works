# Exdson Transpiler

I have seen lots of people who have been working hard on labs and studying programming langs. Here's the compiler built for student who are curious to study about compiler. The students can edit the syntax of the compiler.


## Overview
Ex# (Excelon #) is a programming language simple programming language syntax to understand the compiler. By analyzing this open-source compiler, you can understand how the common compiler are working. 

*How it's working?*  
This Compiler translates the programming language written inside the compiler program into C, compiles it.

*The Ex# transpiler is flexible with syntax.*  
You can update the compiler by implementing your syntax. 


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

