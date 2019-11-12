CC=g++
CFLAGS=-std=c++17 -O2
all: matrix

matrix: main.o matrix.o
	$(CC) -o matrix main.o matrix.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

matrix.o: matrix.cpp
	$(CC) $(CFLAGS) -c matrix.cpp

test:
	./matrix

run:
	./matrix

clean:
	rm -rf matrix test *.o
