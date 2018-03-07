
CC = clang++ -I /usr/include/eigen3

CXXFLAGS  = -std=c++11 -Wall -fopenmp=libomp #-msse2

default: main

main:  main.o
	$(CC) $(CXXFLAGS) -o main main.o

main.o:  main.cpp linked_list.h
	$(CC) $(CXXFLAGS) -c main.cpp

clean:
	$(RM) count *.o *~
