CC=g++
FLAGS=-std=c++2a -Wall -pedantic -Wextra -Werror
TEST_LIBS=-lgtest_main -lgtest -lpthread

all: main test

main: main.cpp serializer.o deserializer.o
	$(CC) $(FLAGS) deserializer.o serializer.o main.cpp -o main

serializer.o: serializer.cpp serializer.hpp
	$(CC) $(FLAGS) serializer.cpp -c

deserializer.o: deserializer.cpp deserializer.hpp
	$(CC) $(FLAGS) deserializer.cpp -c

test: deserializer.o serializer.o test.cpp
	$(CC) $(FLAGS) deserializer.o serializer.o test.cpp -o test $(TEST_LIBS)