CC=g++
FLAGS=-std=c++2a -Wall -pedantic -Wextra
TEST_LIBS=-lgtest_main -lgtest -lpthread

all: main test
	./test

main: main.cpp bigint.o
	$(CC) $(FLAGS) bigint.o main.cpp -o main

bigint.o: bigint.cpp bigint.hpp
	$(CC) $(FLAGS) bigint.cpp -c

test: bigint.o test.cpp
	$(CC) $(FLAGS) bigint.o test.cpp -o test $(TEST_LIBS)