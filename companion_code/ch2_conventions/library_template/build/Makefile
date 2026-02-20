# Minimal library build script placeholder.
# Replace with your project's actual build instructions.
#
# Example usage:
#   cd build/
#   make clean && make
#   # Artifact appears in ../dist/

.PHONY: all clean

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra
AR = ar

SRC_DIR = ../src
INC_DIR = ../inc
DIST_DIR = ../dist

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:.c=.o)
LIB = $(DIST_DIR)/libmodule.a

all: $(LIB)

$(LIB): $(OBJS) | $(DIST_DIR)
	$(AR) rcs $@ $^

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@

$(DIST_DIR):
	mkdir -p $(DIST_DIR)

clean:
	rm -f $(SRC_DIR)/*.o
	rm -f $(LIB)
