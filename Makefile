CC=g++
CFLAGS=-Wall

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

read_input.o: read_input.cpp
	$(CC) $(CFLAGS) -c read_input.cpp

.PHONY: clean

clean:
	rm -f *.o
