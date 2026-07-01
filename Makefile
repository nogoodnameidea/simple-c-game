CC = gcc

all: main

main:
	$(CC) -o main main.c -lwinmm

clean:
	rm *.exe
