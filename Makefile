#Standard Makefile


CFLAGS=-Wall -g


all: ex19
ex19: object.o
clean:
	rm -f ex19.c object.o
exec:
	./ex19


