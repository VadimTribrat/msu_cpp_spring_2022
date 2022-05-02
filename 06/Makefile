CC=g++
FLAGS=-std=c++2a -Wall -pedantic -Wextra
TEST_LIBS=-lgtest_main -lgtest -lpthread

all: test
	./test

test: test.cpp
	$(CC) $(FLAGS) test.cpp -o test $(TEST_LIBS)