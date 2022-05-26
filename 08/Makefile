CC=g++
FLAGS=-std=c++2a -Wall
TEST_LIBS=-lgtest_main -lgtest -pthread

all: test  main.o

main.o: main.cpp pool.o
	${CC} ${FLAGS} main.cpp pool.o -o main -pthread

pool.o: pool.cpp pool.hpp
	${CC} ${FLAGS} pool.cpp -c -pthread

test: test.cpp pool.o
	$(CC) $(FLAGS) test.cpp pool.o -o test $(TEST_LIBS)