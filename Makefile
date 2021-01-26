#Standard Makefile

CC=clang
CFLAGS=-Wall
OBJ=ex23

all:
	$(CC) $(CFLAGS) ex23.c -o $(OBJ)
ex19:
	

clean:
	rm -f ex23.c
exec:
	./ex23


