V =		0.2
CC =		clang
CFLAGS =	-std=c99 -Wall -pedantic
CFLAGS +=	-O2 -pipe

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

release:
	tar evczf passgen-$(V).tgz *.c *.h Makefile passgen.1 README.md LICENSE
	sha256 -h SHA256 passgen-$(V).tgz

clean:
	rm -f *.o
	rm -f passgen
	rm -f test-util
	rm -f passgen-$(V).tgz
	rm -f SHA256
