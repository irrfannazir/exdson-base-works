CC = gcc

INCLUDES = -I include

CFLAGS = $(INCLUDES) -g -Wunused-function -Wall -Wextra

ifeq ($(OS),Windows_NT)
    MKDIR = if not exist "$(subst /,\,$(dir $@))" mkdir "$(subst /,\,$(dir $@))"
    RM = rmdir /S /Q
    DEL = del /Q
    EXE = .exe
else
    MKDIR = mkdir -p $(dir $@)
    RM = rm -rf
    DEL = rm -f
    EXE =
endif

SRC = main.c \
      $(wildcard src/*.c) \
      $(wildcard src/compiler/*.c) \
      $(wildcard src/core/*.c) \
      $(wildcard src/lexer/*.c) \
      $(wildcard src/parser/*.c)

# Object directory
OBJDIR = obj

# Convert source files to object files inside obj/
OBJ = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

# Final executable name
TARGET = ex-c$(EXE)

# Default target
all: $(TARGET)

# Link all object files
$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET)

$(OBJDIR)/%.o: %.c
	@$(MKDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean build files
clean:
	-$(RM) $(OBJDIR)
	-$(RM) build
	-$(DEL) ex-c$(EXE)

.PHONY: all clean
