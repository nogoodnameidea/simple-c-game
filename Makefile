CC = gcc

all: main

main:
	$(CC) -o main main.c game_logic/*.c graphics/graphics.c audio/*.c -lole32 -luuid -lwinmm

clean:
	rm *.exe
