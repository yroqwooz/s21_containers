CC = gcc -lstdc++ -std=c++17 
CXXFLAGS = -Wall -Wextra -Werror 
LDFLAGS = -lgtest 
GCOVFLAGS = -fprofile-arcs -ftest-coverage
SOURCES = lib/*/s21_*.cc

ifeq ($(shell uname), Linux) 
LDFLAGS += -pthread -lrt -lm 
endif

TEST_MAIN = ./tests/s21_tests.cc 

LIST_TESTS = ./tests/s21_list_test.cc 
ARRAY_TESTS = ./tests/s21_array_test.cc 
VECTOR_TESTS = ./tests/s21_vector_test.cc 
QUEUE_TESTS = ./tests/s21_queue_test.cc 
MAP_TESTS = ./tests/s21_map_test.cc 
STACK_TESTS = ./tests/s21_stack_test.cc 
MULTISET_TESTS = ./tests/s21_multiset_test.cc 
SET_TESTS = ./tests/s21_set_test.cc 

.PHONY: all test clean 

all: stylecheck gcov_report 

test: clean 
	$(CC) $(TEST_MAIN) $(LIST_TESTS) $(QUEUE_TESTS) $(MAP_TESTS) $(STACK_TESTS) $(MULTISET_TESTS) $(SET_TESTS) $(ARRAY_TESTS) $(VECTOR_TESTS) -o tests_suite $(LDFLAGS) 
	./tests_suite

list_test: 
	$(CC) $(LIST_TESTS) $(TEST_MAIN) -o test_list $(LDFLAGS) 
	./test_list

array_test: 
	$(CC) $(ARRAY_TESTS) $(TEST_MAIN) -o test_array $(LDFLAGS) 
	./test_array

vector_test: 
	$(CC) $(VECTOR_TESTS) $(TEST_MAIN) -o test_vector $(LDFLAGS) 
	./test_vector

queue_test:
	$(CC) $(QUEUE_TESTS) $(TEST_MAIN) -o test_queue $(LDFLAGS) 
	./test_queue

map_test: 
	@clear
	$(CC) $(MAP_TESTS) $(TEST_MAIN) -o test_map $(LDFLAGS)
	time ./test_map

stack_test: 
	@clear
	$(CC) $(STACK_TESTS) $(TEST_MAIN) -o test_stack $(LDFLAGS)
	time ./test_stack

multiset_test: 
	@clear
	$(CC) $(MULTISET_TESTS) $(TEST_MAIN) -o test_multiset $(LDFLAGS)
	time ./test_multiset

set_test: 
	@clear
	$(CC) $(SET_TESTS) $(TEST_MAIN) -o test_set $(LDFLAGS)
	time ./test_set

# gcov_report: clean
# 	$(CC) $(LDFLAGS) $(GCOVFLAGS) --coverage $(TEST_MAIN) $(MAP_TESTS) $(LIST_TESTS) $(QUEUE_TESTS) $(STACK_TESTS) $(MULTISET_TESTS) $(SET_TESTS) $(ARRAY_TESTS) $(VECTOR_TESTS) -o test_gcov
# 	chmod +x *
# 	./test_gcov
# 	lcov  --ignore-errors inconsistent -t "test" -o gcov.info --no-external -c -d .
# 	rm -rf ./*.gc*
# 	genhtml gcov.info --ignore-errors inconsistent --output-directory report
# 	open ./report/index.html

gcov_report: clean
	$(CC) $(LDFLAGS) $(GCOVFLAGS) --coverage $(TEST_MAIN) $(MAP_TESTS) $(LIST_TESTS) $(QUEUE_TESTS) $(STACK_TESTS) $(MULTISET_TESTS) $(ARRAY_TESTS) $(VECTOR_TESTS) -o test_gcov
	chmod +x *
	./test_gcov
	lcov  --ignore-errors mismatch -t "test" -o gcov.info --no-external -c -d .
	rm -rf ./*.gc*
	genhtml gcov.info --ignore-errors inconsistent  --output-directory report
	open ./report/index.html

stylecheck:
	clang-format -style=Google -n ./lib/*/*.*
	clang-format -style=Google -n ./tests/*.*

styleapply:
	clang-format -style=Google -i ./lib/*/*.*
	clang-format -style=Google -i ./tests/*.*

valgrind: test
	CK_FORK=no valgrind --vgdb=no --log-file="valgrind.log" --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./tests_suite

clean:
	@rm -f a.out test temp valgrind.log *.o *.a *.info *.gc* test_* tests_suite
	@rm -f test_list
	@rm -rf ./gcovr ./report
