CC=gcc
CFLAGS=-Wall
trap: main.o trap.o func.o

clean:
	rm -f main main.o trap.o func.o