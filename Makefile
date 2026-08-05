CC = gcc

all: main

main:
	$(CC) -o main main.c game_logic/*.c graphics/graphics.c audio/music.c -lwinmm

clean:
	rm *.exe
