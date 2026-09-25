#include <stdio.h>
#include "graphics.h"

void drawTopUIHorizontalLine();
void drawTopUIVerticalPiece();
void printTopUISpaces(int spacesNum);

void drawTopUI(HANDLE stdOutHandle, int time, Tank player) {
		SetConsoleTextAttribute(stdOutHandle, 0x07);

		drawTopUIHorizontalLine();
		drawTopUIVerticalPiece();
		drawTopUIVerticalPiece();

		printf("|");
		printTopUISpaces(6);

		printf("Time: %.4d", time);

		printTopUISpaces(3);
		if (player.hasKey == 1) {
			printf("T");
		} else {
			printf(" ");
		}
		printTopUISpaces(3);

		printf("|\n");
		
		drawTopUIHorizontalLine();
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
				
	if (mapPosX == player->posX && mapPosY == player->posY) {
		drawTank(stdOutHandle, player->dir, player->bg);
	} else {
		printf("%s", tileCharacter);
	}

}

void drawBeachMap(HANDLE stdOutHandle, int mapPosX, int mapPosY, Tank *player, int waterLevel) {
	SetConsoleTextAttribute(stdOutHandle, 0x6e);

	int waterLeveLimit = 11;

	if (mapPosX == player->posX && mapPosY == player->posY) {
		drawTank(stdOutHandle, player->dir, player->bg);
	} else if (waterLevel < waterLeveLimit) {
		SetConsoleTextAttribute(stdOutHandle, 0x19);
		printf("~");
	} else { 
		printf("."); 
	}
}

void drawForestMap(HANDLE stdOutHandle, int mapPosX, int mapPosY, Tank *player, int bgColor) {
	SetConsoleTextAttribute(stdOutHandle, bgColor);
	Object key = {.posX = 12, .posY = 5};
	
	if (mapPosX == player->posX && mapPosY == player->posY) {
		drawTank(stdOutHandle, player->dir, player->bg);
	} else if ((mapPosX == key.posX && mapPosY == key.posY) && (player->hasKey == 0)) {
		SetConsoleTextAttribute(stdOutHandle, 0x2e);
		printf("T");
	} else {
		printf(",");
	}
}

void drawGateMap(HANDLE stdOutHandle, int mapPosX, int mapPosY, Tank *player) {
	SetConsoleTextAttribute(stdOutHandle, 0x2A);

	int wallandGateVerticalEndPoint = 6;
	int gateVerticalStartPoint = 2;
	int gateHorizontalStartPoint = 9;
	int gateHorizontalEndPoint = 13;
				
	if (mapPosX == player->posX && mapPosY == player->posY) {
		drawTank(stdOutHandle, player->dir, player->bg);
	} else if (mapPosY >= gateVerticalStartPoint && mapPosY <= wallandGateVerticalEndPoint && mapPosX >= gateHorizontalStartPoint && mapPosX <= gateHorizontalEndPoint) {
		SetConsoleTextAttribute(stdOutHandle, 0x6e);
		printf("-");
	} else if (mapPosY <= wallandGateVerticalEndPoint) {
		SetConsoleTextAttribute(stdOutHandle, 0x87);
		printf(" ");
	} else {
		printf(",");
	}

}

void drawTopUIHorizontalLine() {
	printf("+");
	for (int i = 0; i < 23; i++) {
		printf("-");
	}	
	printf("+\n");
}

void drawTopUIVerticalPiece() {
	printf("|");
	for (int i = 0; i < 23; i++) {
		printf(" ");
	}
	printf("|\n");
}

void printTopUISpaces(int spacesNum) {
	for (int i = 0; i < spacesNum; i++) {
		printf(" ");
	}
}