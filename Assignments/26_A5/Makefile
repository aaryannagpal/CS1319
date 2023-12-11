.SUFFIXES:

CC=gcc
CFLAGS=-Wall -Werror

SRC=26_A5_translator.c
OBJ=$(SRC:.c=.o)
EXECUTABLE=translator

all: build

translator: 26_A5.y 26_A5_translator.c 26_A5.l
	bison -d 26_A5.y
	flex -o lex.yy.c 26_A5.l
	gcc 26_A5_translator.c 26_A5.tab.c lex.yy.c -lfl -Werror -o translator

build: translator

test: build
	./$(EXECUTABLE) < 26_A5.nc > test.out

open: build
	./$(EXECUTABLE) < 26_A5.nc

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

asm: build
	for i in 1 2 3 4 5 ; do \
		echo "Running test case $$i"; \
		./$(EXECUTABLE) < A5_Tests/test$$i.nc > A5_Quads/quads$$i.tac; \
		as -o test$$i.o A5_Quads/quads$$i.tac; \
		ld -o test$$i test$$i.o; \
		./test$$i > A5_ASM/output$$i.txt; \
	done

clean:
	rm -f $(OBJ) $(EXECUTABLE) output.asm
	rm -f lex.yy.c 26_A5.tab.c 26_A5.tab.h translator
	rm -f A5_Quads/* A5_ASM/*
	rm -f test*.o test*

.PHONY: all build test clean

