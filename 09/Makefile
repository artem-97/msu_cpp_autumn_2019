CC=g++
CFLAGS=-std=c++17 -O2 -pthread

run: generate sort check

generate: generate.cpp
	$(CC) $(CFLAGS) generate.cpp -o generate
	./generate

sort: main.cpp
	$(CC) $(CFLAGS) main.cpp -o sort
	./sort input

check: generate sort
	$(CC) $(CFLAGS) check.cpp -o check 
	./check

clean:
	rm generate sort check input res
