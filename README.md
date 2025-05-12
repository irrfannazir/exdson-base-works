# Exdson Compiler

## Overview
Exdson (Excelon Data Structure Object Notation) is a programming language to handle Data Structure with Function-Oriented Syntax. This Open-source Compiler translates Exdson code into C, compiles it. You can update the compiler by implementing your syntax.

## Installation
1. Clone the repository:
   ```sh
   git clone https://github.com/yourusername/exdson-compiler.git
   cd exdson-compiler
   ```
2. Build the compiler (assuming dependencies are installed):
   ```sh
   make
   ```

### Compiling & Running
1. Run the Main Bat file which includes every compilation commands.
   ```sh
   bash com.bat
   ```
3. Write your Exdson program as input.
   An example program for declaring a variable.
   ```sh
   single a = 3+5*3;
   ```
4. It shows the c program which has been executed and shows the details of the compilation.


## Features
1. To activate interactive mode. Comment the 4th line of dependencies.h.
2. To update the compiler with new syntax format. Run
```sh
./update.bat
```
   Then enter the syntax and the syntax to implement in c.

