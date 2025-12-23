CC        := gcc
SRC_FILES := $(wildcard src/*.c)
OBJ_FILES := $(patsubst src/%.c,obj/%.o,$(SRC_FILES))
INCLUDES  := $(wildcard include/*.h)
CFLAGS    := -Iinclude -Wall -Wextra -Wpedantic -Wmisleading-indentation -std=c89 -ansi -O1

LIB_NAME  := libqlibc.a

all: $(LIB_NAME)

# Create object directory if it doesn't exist
obj/%.o: src/%.c | obj
	$(CC) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

$(LIB_NAME): $(OBJ_FILES)
	ar rcs $@ $^

clean:
	rm -rf obj $(LIB_NAME)
	rm -rf *.o
	rm test

# build test program
test: $(LIB_NAME) test.o
	$(CC) -nostdlib -ffreestanding -Iinclude test.o -L. -lqlibc -o test
	./test

test.o: test.c
	$(CC) $(CFLAGS) -c test.c -o test.o

.PHONY: all clean test