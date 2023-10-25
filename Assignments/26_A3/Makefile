build:
	bison -d 26_A3.y
	flex -o lex.yy.c 26_A3.l
	gcc -o parser lex.yy.c 26_A3.tab.c 26_A3.c -lfl -Werror

build-test:
	bison -d 26_A3.y
	flex -o lex.yy.c 26_A3.l
	gcc -o parser lex.yy.c 26_A3.tab.c 26_A3.c -lfl -Werror
	./parser < 26_A3.nc > test.out

test-all:
	bison -d 26_A3.y
	flex -o lex.yy.c 26_A3.l
	gcc -o parser lex.yy.c 26_A3.tab.c 26_A3.c -lfl -Werror
	./parser < sample_output_A3/bubble_sort.nc > output/bubble_sort.output
	./parser < sample_output_A3/corecursive_fibonacci.nc > output/corecursive_fibonacci.output
	./parser < sample_output_A3/error_test.nc > output/error_test.output

clean-test-all:
	rm -f lex.yy.c 26_A3.tab.c 26_A3.tab.h parser
	rm -f output/bubble_sort.output output/corecursive_fibonacci.output output/error_test.output

clean-test:
	rm -f lex.yy.c 26_A3.tab.c 26_A3.tab.h parser
	rm -f test.out

clean:
	rm -f lex.yy.c 26_A3.tab.c 26_A3.tab.h parser