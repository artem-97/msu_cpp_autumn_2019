CC=g++
CFLAGS=-std=c++17 -O2 -pthread

all: main.cpp pool.h
	$(CC) $(CFLAGS) main.cpp -o pool
run:
	./pool
test:
	./pool

clean:
	rm pool
