.SUFFIXES:

CC=gcc
CFLAGS=-Wall -Werror

SRC=26_A5_translator.c
OBJ=$(SRC:.c=.o)
EXECUTABLE=compiler
TEST=./A5_Tests

all: build

compiler: 26_A5.y 26_A5_translator.c 26_A5.l
	bison -d 26_A5.y
	flex -o lex.yy.c 26_A5.l
	gcc 26_A5_translator.c 26_A5.tab.c lex.yy.c -lfl -Werror -o compiler

build: compiler

test: build
	./$(EXECUTABLE) 1 26_A5.nc > test.out
	./$(EXECUTABLE) 2 26_A5.nc > test.asm
	as -o test.o test.asm
	gcc -o test test.o

open: build
	./$(EXECUTABLE) < 26_A5.nc

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

tac: build
	for i in 1 2 3 4 5 6 7; do \
		echo "Running test case $$i"; \
		./$(EXECUTABLE) 1 $(TEST)/test$$i.nc > $(TEST)/tac/quads$$i.out; \
	done

asm: build
	for i in 1 2 3 4 5 6 7; do \
		echo "Running test case $$i"; \
		./$(EXECUTABLE) 2 $(TEST)/test$$i.nc > $(TEST)/asm/asm$$i.asm; \
	done

prog: build
	for i in 1 2 3 4 5 6 7; do \
		echo "Running test case $$i"; \
		./$(EXECUTABLE) 2 $(TEST)/test$$i.nc > $(TEST)/asm/asm$$i.asm; \
		as -o $(TEST)/asm/asm$$i.o $(TEST)/asm/asm$$i.asm; \
		gcc -o $(TEST)/prog/prog$$i $(TEST)/asm/asm$$i.o -no-pie; \
	done

clean:
	rm -f $(OBJ) $(EXECUTABLE) output.asm
	rm -f lex.yy.c 26_A5.tab.c 26_A5.tab.h translator
	rm -f A5_Quads/* A5_ASM/*
	rm -f test*.o test*
	rm -f $(TEST)/tac/* $(TEST)/asm/* $(TEST)/prog/*

.PHONY: all build test clean

