CC = gcc

all: main

main:
	$(CC) -o main main.c game_logic/movement.c game_logic/sections.c graphics/graphics.c -lwinmm

clean:
	rm *.exe
