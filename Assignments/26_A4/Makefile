build:
	bison 26_A3.y --defines=26_A3.tab.h -o 26_A3.tab.c
	flex -o lex.yy.c 26_A3.l
	gcc -o parser lex.yy.c 26_A3.tab.c 26_A3.c -lfl -Werror

build_2:
	bison 26_A3.y --defines=26_A3.tab.h -o 26_A3.tab.c
	flex -o lex.yy.c 26_A3.l
	gcc -o parser lex.yy.c 26_A3.tab.c 26_A3.c -ll -Werror

test:
	bison 26_A3.y --defines=26_A3.tab.h -o 26_A3.tab.c
	flex -o lex.yy.c 26_A3.l
	gcc -o parser lex.yy.c 26_A3.tab.c 26_A3.c -lfl -Werror
	./parser < 26_A3.nc > test.out

test-2:
	bison 26_A3.y --defines=26_A3.tab.h -o 26_A3.tab.c
	flex -o lex.yy.c 26_A3.l
	gcc -o parser lex.yy.c 26_A3.tab.c 26_A3.c -ll -Werror

	./parser < test_cases/array_runtime_error.nc > output/array_runtime_error.output
	./parser < test_cases/factorial.nc > output/factorial.output
	./parser < test_cases/factorial_recursive.nc > output/factorial_recursive.output
	./parser < test_cases/syntax_error.nc > output/syntax_error.output

test-all:
	bison 26_A3.y --defines=26_A3.tab.h -o 26_A3.tab.c
	flex -o lex.yy.c 26_A3.l
	gcc -o parser lex.yy.c 26_A3.tab.c 26_A3.c -lfl -Werror
	./parser < sample_output_A3/bubble_sort.nc > output/bubble_sort.output
	./parser < sample_output_A3/corecursive_fibonacci.nc > output/corecursive_fibonacci.output
	./parser < sample_output_A3/error_test.nc > output/error_test.output
	python3 test-cases.py > output/result.txt

clean-all-test:
	rm -f lex.yy.c 26_A3.tab.c 26_A3.tab.h parser
	rm -f output/bubble_sort.output output/corecursive_fibonacci.output output/error_test.output
	rm -f output/array_runtime_error.output output/factorial.output output/factorial_recursive.output
	rm -f output/nested_function.output output/syntax_error.output
	rm -f output/result.txt
	rm -f test.out

clean-test:
	rm -f lex.yy.c 26_A3.tab.c 26_A3.tab.h parser
	rm -f test.out

clean:
	rm -f lex.yy.c 26_A3.tab.c 26_A3.tab.h parser