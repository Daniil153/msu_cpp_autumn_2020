CC=g++
FLAGS=-std=c++17 -Wall -pedantic -Wextra -Wno-unused-variable

all: main

main: main.o 
	$(CC) main.o $(FLAGS) -o my_prog

main.o: main.cpp format.hpp
	$(CC) $(FLAGS) -c main.cpp

test: 
	./my_prog
