CC=g++
CFLAGS=-std=c++17 -O2
all:formatter

formatter: formatter.cpp formatter.h
	$(CC) $(CFLAGS) -o formatter formatter.cpp

test:
	./formatter
run:
	./formatter
clean:
	rm -rf formatter
