CC=g++
CFLAGS=-std=c++17 -Wall -O2
all: calc

calc: main.o lexer.o parser.o interpreter.o token.o ast.o
	$(CC) -o calc main.o lexer.o parser.o interpreter.o token.o ast.o


main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

lexer.o: lexer.cpp
	$(CC) $(CFLAGS) -c lexer.cpp

parser.o: parser.cpp
	$(CC) $(CFLAGS) -c parser.cpp

interpreter.o: interpreter.cpp
	$(CC) $(CFLAGS) -c interpreter.cpp

token.o: token.cpp
	$(CC) $(CFLAGS) -c token.cpp

ast.o: ast.cpp
	$(CC) $(CFLAGS) -c ast.cpp

run:
	./calc

test:
	python3 test.py

clean:
	rm -rf calc *.o
