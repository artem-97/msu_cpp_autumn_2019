CC=g++
CFLAGS=-std=c++17 -O2
all: allocator

allocator: main.o allocator.o
	$(CC) -o allocator main.o allocator.o

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

allocator.o: allocator.cpp
	$(CC) $(CFLAGS) -c allocator.cpp

test.o: test.cpp
	$(CC) $(CFLAGS) -c test.cpp

make_test: test.o
	$(CC) -o test test.o

run:
	./allocator

test: make_test
	./test


make_bench: bench.cpp
	$(CC) bench.cpp -std=c++17 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o bench

bench: make_bench
	./bench

clean:
	rm -rf allocator bench test *.o
