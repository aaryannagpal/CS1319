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
	gcc 26_A5_translator.c 26_A5.tab.c lex.yy.c -ll -Werror -o translator

build: translator

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

test: build
	@for i in {1,2,3,4,5}; do \
		echo "Running test case $$i"; \
		./$(EXECUTABLE) < test$$i.nc > 26_A5_quads$$i.tac; \
		as -o test$$i.o 26_A5_quads$$i.tac; \
		ld -o test$$i test$$i.o; \
		./test$$i > 26_A5_output$$i.txt; \
	done

clean:
	rm -f $(OBJ) $(EXECUTABLE) output.asm

.PHONY: all build test clean

