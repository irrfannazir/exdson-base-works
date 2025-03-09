# Exdson Compiler

## Overview
Exdson (Excelon Data Structure Object Notation) is a new programming language to handle Data Structure with Function-Oriented Syntax. This Open-source Compiler translates Exdson code into C, compiles it, and executes the resulting program. This conversion will give an idea to developers how the program is executed. We can update the compiler by implementing your syntax.

## Features
- Self-Updating Software: There is another .c file to update the compiler. This allows you to implement the your own creative syntax.

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
3. Run an Exdson program:
   ```sh
   ./exdson your_program.exd
   ```

## Usage

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

