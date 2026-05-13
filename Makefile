# Compiler
CC = gcc

# Output executable
TARGET = ex-c

# Include directories
INCLUDES = -I include

# Source files
SRC = main.c \
      $(wildcard src/*.c) \
      $(wildcard src/compiler/*.c) \
      $(wildcard src/core/*.c) \
      $(wildcard src/lexer/*.c) \
      $(wildcard src/parser/*.c)

# Compiler flags
CFLAGS = $(INCLUDES) -g 
# -Wunused-function -Wall -Wextra

# Default target
all:
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET)

# Clean target
clean:
	rm -f $(TARGET)