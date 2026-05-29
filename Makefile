CC = gcc

all: main

main:
	$(CC) -o main main.c

clean:
	rm main.exe
