# Exdson Compiler

## Overview
Exdson (Excelon Data Structure Object Notation) is a programming language to handle Data Structure with Function-Oriented Syntax. This Open-source Compiler translates Exdson code into C, compiles it. You can update the compiler by implementing your syntax.

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

