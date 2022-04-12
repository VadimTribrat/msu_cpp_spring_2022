CC=g++
FLAGS=-std=c++2a -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

all: main test
	
main: main.cpp matrix.o
	$(CC) $(FLAGS) matrix.o main.cpp -o main

matrix.o: matrix.cpp matrix.hpp
	$(CC) $(FLAGS) matrix.cpp -c

test: matrix.o test.cpp
	$(CC) $(FLAGS) matrix.o test.cpp -o test $(TEST_LIBS)