CC=g++
CFLAGS= -std=c++11
OBJS = lsh.o Methods.o Hashing.o VectorData.o Tools.o Euclidean.o

# Executables
lsh: lsh.o Methods.o Hashing.o VectorData.o Tools.o Euclidean.o
	$(CC) -o lsh $(OBJS)

cube: cube.o Methods.o Hashing.o VectorData.o Tools.o Euclidean.o
	$(CC) -o cube $(OBJS)

# Object files
lsh.o: src/lsh.cpp
	$(CC) $(CFLAGS) -c src/lsh.cpp

cube.o: src/cube.cpp
	$(CC) $(CFLAGS) -c src/cube.cpp

Methods.o: src/Methods.cpp
	$(CC) $(CFLAGS) -c src/Methods.cpp
	
Hashing.o: src/Hashing.cpp
	$(CC) $(CFLAGS) -c src/Hashing.cpp

VectorData.o: src/VectorData.cpp
	$(CC) $(CFLAGS) -c src/VectorData.cpp

Tools.o: src/Tools.cpp
	$(CC) $(CFLAGS) -c src/Tools.cpp
	
Euclidean.o: src/Euclidean.cpp
	$(CC) $(CFLAGS) -c src/Euclidean.cpp

.PHONY: clean

clean:
	rm -f lsh cube $(OBJS)
