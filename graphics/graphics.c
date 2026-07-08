#include <stdio.h>
#include "graphics.h"

void drawTopUI(HANDLE stdOutHandle, int time) {
		SetConsoleTextAttribute(stdOutHandle, 0x07);

		printf("+");
		for (int i = 0; i < 23; i++) {
			printf("-");
		}	
		printf("+\n");

		printf("|");
		for (int i = 0; i < 23; i++) {
			printf(" ");
		}
		printf("|\n");

		printf("|");
		for (int i = 0; i < 23; i++) {
			printf(" ");
		}
		printf("|\n");

		printf("|");
		for (int i = 0; i < 6; i++) {
			printf(" ");
		}	

		printf("Time: %.4d", time);

		for (int i = 0; i < 7; i++) {
			printf(" ");
		}	
		printf("|\n");

		printf("+");
		for (int i = 0; i < 23; i++) {
			printf("-");
		}
		printf("+\n");
}

void drawTank(HANDLE stdOutHandle, TankDirection tDir, TankBackground tBg) {
	switch (tBg) {
		case 1:
			SetConsoleTextAttribute(stdOutHandle, 0x67);
			break;
		case 2:
			SetConsoleTextAttribute(stdOutHandle, 0x87);
			break;
		default:
			SetConsoleTextAttribute(stdOutHandle, 0x27);
			break;
	}
	switch (tDir) {
		case 1:
			printf("<");
			break;
		case 2:
			printf(">");
			break;
		case 3:
			printf("v");
			break;
		default:
			printf("^");
			break;
	}
}

void drawMap(HANDLE stdOutHandle, int mapPosX, int mapPosY, Tank *player, int bgColor, char *tileCharacter) {
	SetConsoleTextAttribute(stdOutHandle, bgColor);
				
	if (mapPosX == player->posY && mapPosY == player->posX) {
		drawTank(stdOutHandle, player->dir, player->bg);
	} else {
		printf("%s", tileCharacter);
	}
}

void drawBeachMap(HANDLE stdOutHandle, int mapPosX, int mapPosY, Tank *player, int bgColor, int waterLevel, char *tileCharacter) {
	SetConsoleTextAttribute(stdOutHandle, bgColor);

	int waterLeveLimit = 11;

	if (mapPosX == player->posY && mapPosY == player->posX) {
		drawTank(stdOutHandle, player->dir, player->bg);
	} else if (waterLevel < waterLeveLimit) {
		SetConsoleTextAttribute(stdOutHandle, 0x19);
		printf("~");
	} else { 
		printf("%s", tileCharacter); 
	}
}

void drawForestMap(HANDLE stdOutHandle, int mapPosX, int mapPosY, Tank *player, int bgColor, Tree trees[5]) {
	SetConsoleTextAttribute(stdOutHandle, bgColor);
				
	if (mapPosX == player->posY && mapPosY == player->posX) {
		drawTank(stdOutHandle, player->dir, player->bg);
	} else if (mapPosX == trees[0].logPosX && mapPosY == trees[0].logPosY) {

	} else {
		printf(",");
	}



	// TODO: Add trees
}
