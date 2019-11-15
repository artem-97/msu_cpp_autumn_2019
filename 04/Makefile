CC=g++
CFLAGS=-std=c++17 -O2
all:bigint

bigint: bigint.o vector.o main.o
	$(CC) -o bigint bigint.o vector.o main.o

bigint.o: bigint.cpp
	$(CC) $(CFLAGS) -c bigint.cpp

vector: vector.o
	$(CC) -o vector vector.o

vector.o: vector.cpp
	$(CC) $(CFLAGS) -c vector.cpp

main.o:	main.cpp
	$(CC) $(CFLAGS) -c main.cpp

test:
	./bigint
run:
	./bigint
clean:
	rm -rf vector bigint test *.o
