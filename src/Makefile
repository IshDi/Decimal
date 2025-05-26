CC=gcc
CFLAGS=-g -Wall -Werror -Wextra -std=c11
TESTCFLAGS=$(CFLAGS) $(shell pkg-config --cflags check) #-fsanitize=address
TESTLDFLAGS=$(shell pkg-config --libs check)

all: test s21_decimal.a

s21_decimal.a:
	$(CC) -c $(CFLAGS) s21_arithmetic.c s21_another_functions.c s21_comparison.c s21_converters.c
	ar rc s21_decimal.a *.o
	ranlib s21_decimal.a

coverege_decimal.a: 
	$(CC) -c $(CFLAGS) -fprofile-arcs -ftest-coverage s21_arithmetic.c s21_another_functions.c s21_comparison.c s21_converters.c
	ar rc coverege_decimal.a *.o
	ranlib coverege_decimal.a

test: s21_decimal.a 
	$(CC) $(TESTCFLAGS) -c tests/*.c tests/main.c
	$(CC) *.o $(TESTCFLAGS) $(TESTLDFLAGS) s21_decimal.a -o s21_test_runner

gcov_report: clean coverege_decimal.a
	$(CC) $(TESTCFLAGS) -c tests/*.c tests/main.c
	$(CC) -fprofile-arcs -ftest-coverage *.o $(TESTCFLAGS) $(TESTLDFLAGS) coverege_decimal.a -o test_gcov
	./test_gcov
	geninfo . -o coverage.info
	genhtml coverage.info -o ./coverage

clean:
	rm -f *.o s21_decimal.a coverege_decimal.a s21_test_runner test_gcov coverage.info
	rm -rf coverage
	rm -f *.gcda *.gcno

rebuild: clean all

debug:
	echo $(TESTCFLAGS) $(TESTLDFLAGS)