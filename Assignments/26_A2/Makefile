all: 26_A2.nc
	flex 26_A2.l
	gcc lex.yy.c 26_A2.c -ll -o lexer
	./lexer < 26_A2.nc

build:
	flex 26_A2.l
	gcc lex.yy.c 26_A2.c -ll -o lexer

clean:
	rm -f lex.yy.c lexer