.SUFFIXES: 

parser: 26_A4.y 26_A4.c 26_A4.l
	bison -d 26_A4.y
	flex -o lex.yy.c 26_A4.l
	gcc 26_A4.c 26_A4.tab.c lex.yy.c -lfl -Werror -o parser

build: parser

test: parser
	./parser < Test.calc