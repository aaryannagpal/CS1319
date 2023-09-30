all: 26_A2.nc
	flex 26_A2.l
	gcc lex.yy.c 26_A2.c -ll -o lexer.out
	./lexer.out < 26_A2.nc

build:
	flex 26_A2.l
	gcc lex.yy.c 26_A2.c -ll -o lexer.out

clean:
	rm -f lex.yy.c lexer.out