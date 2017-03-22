CC     = clang
CFLAGS = -O2 -pipe -std=c99 -Wall -pedantic

all: passgen

tests: test-util

passgen: passgen.o main.c
	$(CC) $(CFLAGS) main.c passgen.o -o passgen

passgen.o: passgen.h
	$(CC) $(CFLAGS) -c passgen.c -o passgen.o

test-util: util.o test-util.c
	$(CC) $(CFLAGS) test-util.c util.o -o test-util

install:
	install -S -m 0740 passgen ~/bin

clean:
	rm -f passgen.o
	rm -f passgen
	rm -f test-util
