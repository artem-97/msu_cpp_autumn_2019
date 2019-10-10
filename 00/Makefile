CC=g++
CFLAGS=-std=c++14

all: matrix

matrix: main.o timer.o
	$(CC) -o matrix main.o timer.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

timer.o: timer.cpp
	$(CC) $(CFLAGS) -c timer.cpp

run:
	./matrix

test:
	./matrix

clean:
	rm -rf matrix *.o
