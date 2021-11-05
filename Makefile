CC=g++
CFLAGS= -std=c++11 -Wall
OBJS = main.o read_input.o Hashing.o Euclidean.o

lsh: main.o read_input.o Hashing.o Euclidean.o
	$(CC) -o lsh $(OBJS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

read_input.o: read_input.cpp
	$(CC) $(CFLAGS) -c read_input.cpp
	
Hashing.o: Hashing.cpp
	$(CC) $(CFLAGS) -c Hashing.cpp
	
Euclidean.o: Euclidean.cpp
	$(CC) $(CFLAGS) -c Euclidean.cpp

.PHONY: clean

clean:
	rm -f lsh $(OBJS)
