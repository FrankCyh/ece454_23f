CFLAGS := -fprofile-arcs -ftest-coverage -Wall -Werror
LOADLIBES := -lgcov

all: gcov_test_1 gcov_test_2

gcov_test_1: gcov_test_1.o
gcov_test_2: gcov_test_2.o

clean:
	rm -f gcov_test_1 gcov_test_2 *.o *.gcov *.gcda *.gcno
