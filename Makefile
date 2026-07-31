CC = gcc

all: main

main:
	$(CC) -o main main.c game_logic/*.c graphics/graphics.c -lwinmm

clean:
	rm *.exe
