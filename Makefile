# Compiler
CC = gcc

# Output executable
TARGET = ex-c

# Include directories
INCLUDES = -I lex \
           -I alt-parse \
           -I alt-compile \
           -I lex/include \
           -I alt-parse/include \
           -I alt-compile/include \
           -I include

# Source files
SRC = main.c \
      src/* \
      lex/lex.c \
      lex/src/* \
      alt-parse/parse.c \
      alt-parse/src/* \
      alt-compile/compile.c \
      alt-compile/src/*

# Compiler flags
CFLAGS = $(INCLUDES) \
         -g -Wunused-function -Wall -Wextra

# Default target
all:
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)

# Clean target
clean:
	rm -f $(TARGET)