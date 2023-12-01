.SUFFIXES: 

translator: 26_A4.y 26_A4_translator.c 26_A4.l
	bison -d 26_A4.y
	flex -o lex.yy.c 26_A4.l
	gcc 26_A4_translator.c 26_A4.tab.c lex.yy.c -lfl -Werror -o translator

build: translator

test: translator
	./translator < 26_A4.nc > test.out

open: translator
	./translator < 26_A4.nc

clean: 
	rm -f lex.yy.c 26_A4.tab.c 26_A4.tab.h translator
	rm -f test.out