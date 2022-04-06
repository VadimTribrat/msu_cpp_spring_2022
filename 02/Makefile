CC=g++
FLAGS=-std=c++2a -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

all: main test
	
main: main.cpp parser.o
	$(CC) $(FLAGS) parser.o main.cpp -o main

parser.o: parser.cpp parser.hpp
	$(CC) $(FLAGS) parser.cpp -c

test: parser.o test.cpp
	$(CC) $(FLAGS) parser.o test.cpp -o test $(TEST_LIBS)