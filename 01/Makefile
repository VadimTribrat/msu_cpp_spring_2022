CC=g++
FLAGS=-std=c++2a -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

all: main test
	./test
	
main: main.cpp allocator.o
	$(CC) $(FLAGS) allocator.o main.cpp -o main

allocator.o: allocator.cpp allocator.h
	$(CC) $(FLAGS) allocator.cpp -c

test: allocator.o test.cpp
	$(CC) $(FLAGS) allocator.o test.cpp -o test $(TEST_LIBS)
