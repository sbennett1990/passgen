#CC = gcc
CC = clang

CFLAGS = -std=c99 -Wall#-Werror

all: passgen

tests: test-util

passgen: util.o passgen.c
	$(CC) $(CFLAGS) passgen.c util.o -o passgen

util.o: util.h
	$(CC) $(CFLAGS) -c util.c -o util.o

test-util: util.o test-util.c
	$(CC) $(CFLAGS) test-util.c util.o -o test-util

clean:
	rm -f util.o
	rm -f passgen
	rm -f test-util
