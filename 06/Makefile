CC=g++
FLAGS=-std=c++2a -Wall -pedantic -Wextra
TEST_LIBS=-lgtest_main -lgtest -lpthread

all: test format.o
	./test

format.o: format.cpp
	$(CC) $(FLAGS) format.cpp -c	

test: test.cpp format.o
	$(CC) $(FLAGS) test.cpp -o test $(TEST_LIBS)