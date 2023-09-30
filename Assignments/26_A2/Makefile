all: 26_A2.nc
	flex 26_A2.l
	gcc lex.yy.c 26_A2.c -ll -o 26_A2.out
	./26_A2.out < 26_A2.nc

clean:
	rm -f lex.yy.c 26_A2.out