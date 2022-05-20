CC=g++
FLAGS=-std=c++2a -Wall
TEST_LIBS=-lgtest_main -lgtest -lpthread

all: test  main.cpp
	valgrind ./test

test: test.cpp vector.hpp
	$(CC) $(FLAGS) test.cpp -o test $(TEST_LIBS)