# Exdson Compiler

## Overview
Exdson (Excelon Data Structure Object Notation) is a new programming language that blends function-based programming (FOP) with an object-oriented syntax similar to Python. The Exdson compiler translates Exdson code into C, compiles it, and executes the resulting program. The core idea is to allow developers to express data structure algorithms using OOP-style syntax while ensuring function-based implementation.

## Features
- **Function-Based Execution:** Despite using an OOP-like syntax, Exdson ensures implementation follows function-based programming principles.
- **Python-Like Syntax:** Designed for ease of learning and readability.
- **C Code Generation:** The compiler translates Exdson programs into C for compilation and execution.
- **Data Structure Integration:** Built to implement every data structure algorithm efficiently.
- **Compiler Update Software:** A separate software module allows users to modify the compiler by submitting queries to customize its behavior.

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
### Writing an Exdson Program
The implementation is not yet developed.


### Compiling & Running
1. Run the Main Bat file which includes every compilation commands.
   ```sh
   ./com.bat
   ```
3. Write your Exdson program as input.
   An example program for declaring a variable.
   ```sh
   single a = 3+5*3;
   ```
4. It shows the c program which has been executed and shows the details of the compilation.


## Future Plans
- **Expanded Syntax Support**: Improve syntax to support implementing different data structures.
- **Optimization Enhancements**: Update the program to convert the program into ASM Language.
- **Community Contributions**: Open to contributions for new features and having fun.


## Contributing
1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push the branch and submit a pull request

## License
This project is licensed under the MIT License. See the LICENSE file for details.

## Contact
For inquiries, feature requests, or issues, open an issue on GitHub or contact the development team.

