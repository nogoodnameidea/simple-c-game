#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>

#include "game_logic/enums.h"
#include "game_logic/structs.h"
#include "game_logic/macros.h"

void drawTopUI(HANDLE stdOutHandle, int time);
void drawTank(HANDLE stdOutHandle, TankDirection tDir, TankBackground tBg);
void drawMap(HANDLE stdOutHandle, int mapPosX, int mapPosY, Tank *player, int bgColor, char *tileCharacter);
void drawBeachMap(HANDLE stdOutHandle, int mapPosX, int mapPosY, Tank *player, int bgColor, int waterLevel, char *tileCharacter);
void drawForestMap(HANDLE stdOutHandle, int mapPosX, int mapPosY, Tank *player, int bgColor, Tree trees[5]);

MovementReturnCode movement(Tank *player, int maxX, int minX, int maxY, int minY);
MovementReturnCode beachMovement(Tank *player, int maxX, int minX, int maxY, int minY);
MovementReturnCode forestMovement(Tank *player, int maxX, int minX, int maxY, int minY);

void sectionOne(Tank *player, HANDLE stdOutHandle, int *quarterSecondCounter, int *seconds);
void sectionTwo(Tank *player, HANDLE stdOutHandle, int *quarterSecondCounter, int *seconds);
void sectionThree(Tank *player, HANDLE stdOutHandle, int *quarterSecondCounter, int *seconds);
void sectionFour(Tank *player, HANDLE stdOutHandle, int *quarterSecondCounter, int *seconds);

int main() {
	HANDLE stdOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleOutputCP(CP_UTF8);
	
	Tank player = {
		.posX = 12,
		.posY = 9,
		.dir = DIR_UP,
		.bg = BG_CONCRETE,
		.currentSection = SECTION_ONE,
	};

	int quarterSecondCounter = 0;
	int seconds = 0;

	int isRunning = 1;

	PlaySound("audio/music.wav", NULL, SND_FILENAME | SND_ASYNC);

	system("cls");
	while (isRunning == 1) {
		switch (player.currentSection) {
			case SECTION_ONE:
				sectionOne(&player, stdOutHandle, &quarterSecondCounter, &seconds);
				break;
			case SECTION_TWO:
				sectionTwo(&player, stdOutHandle, &quarterSecondCounter, &seconds);
				break;
			case SECTION_THREE:
				sectionThree(&player, stdOutHandle, &quarterSecondCounter, &seconds);
				break;
			case SECTION_FOUR:
				sectionFour(&player, stdOutHandle, &quarterSecondCounter, &seconds);
				break;
			default:
				isRunning = 0;
				break;
		}
	}

	return 0;
}

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
	} else {
		printf(",");
	}

	// TODO: Add trees
}

MovementReturnCode movement(Tank *player, int maxX, int minX, int maxY, int minY) {
	if (QUIT_GAME_KEY_PRESSED) {
		return EXIT;
	}
		
	if (MOVE_UP_KEY_PRESSED) {
		if (player->posY >= minY) {
			player->posY--;
			player->dir = DIR_UP;
		}
	}

	if (MOVE_DOWN_KEY_PRESSED) {
		if (player->posY <= maxY) {
			player->posY++;
			player->dir = DIR_DOWN;
		}
	}

	if (MOVE_LEFT_KEY_PRESSED) {
		if (player->posX >= maxX) {
			player->posX--;
			player->dir = DIR_LEFT;
		}
	}

	if (MOVE_RIGHT_KEY_PRESSED) {
		if (player->posX <= minX) {
			player->posX++;
			player->dir = DIR_RIGHT;
		}
	}
}

MovementReturnCode beachMovement(Tank *player, int maxX, int minX, int maxY, int minY){
	if (QUIT_GAME_KEY_PRESSED) {
		return EXIT;
	}
		
	if (MOVE_UP_KEY_PRESSED) {
		if (player->posY >= minY) {
			player->posY--;
			player->dir = DIR_UP;
		}
	}

	if (MOVE_DOWN_KEY_PRESSED) {
		if (player->posY <= maxY) {
			player->posY++;
			player->dir = DIR_DOWN;
		}
	}

	if ((MOVE_LEFT_KEY_PRESSED) && (player->posX >= 12)) {
		if (player->posX >= maxX) {
			player->posX--;
			player->dir = DIR_LEFT;
		}
	}

	if ((MOVE_RIGHT_KEY_PRESSED)) {
		if (player->posX <= minX) {
			player->posX++;
			player->dir = DIR_RIGHT;
		}
	}
}

MovementReturnCode forestMovement(Tank *player, int maxX, int minX, int maxY, int minY) {
	if (QUIT_GAME_KEY_PRESSED) {
		return EXIT;
	}
		
	if (MOVE_UP_KEY_PRESSED) {
		if (player->posY >= minY) {
			player->posY--;
			player->dir = DIR_UP;
		}
	}

	if (MOVE_DOWN_KEY_PRESSED) {
		if (player->posY <= maxY) {
			player->posY++;
			player->dir = DIR_DOWN;
		}
	}

	if (MOVE_LEFT_KEY_PRESSED) {
		if (player->posX >= maxX) {
			player->posX--;
			player->dir = DIR_LEFT;
		}
	}

	if (MOVE_RIGHT_KEY_PRESSED) {
		if (player->posX <= minX) {
			player->posX++;
			player->dir = DIR_RIGHT;
		}
	}

	// TODO: Tree colision
}

void sectionOne(Tank *player, HANDLE stdOutHandle, int *quarterSecondCounter, int *seconds) {
	GAME_CLOCK_LOOP {
		COORD redrawPosition = {0,0};
		SetConsoleCursorPosition(stdOutHandle, redrawPosition);

		int i = 0;
		int j = 0;

		drawTopUI(stdOutHandle, *seconds);

		Y_LOOP {
			X_LOOP {
				drawMap(stdOutHandle, i, j, player, 0x87, " ");
			}
			SetConsoleTextAttribute(stdOutHandle, 0x07);
			printf("\n");
		}

		if (*quarterSecondCounter > 4) {
			*quarterSecondCounter = 0;
			*seconds += 1;
		}

		MovementReturnCode mrc = movement(player, 1, 24, 8, -1);

		Sleep(150);

		if (mrc == EXIT) {
			player->currentSection = EXIT_GAME;
			break;
		}

		if (player->posY == -1) {
			player->currentSection = SECTION_TWO;
			player->posY = 9;
			player->bg = BG_GRASS;
			break;
		}
	}
}

void sectionTwo(Tank *player, HANDLE stdOutHandle, int *quarterSecondCounter, int *seconds) {
	GAME_CLOCK_LOOP {
		COORD redrawPosition = {0,0};
		SetConsoleCursorPosition(stdOutHandle, redrawPosition);

		int i = 0;
		int j = 0;


		drawTopUI(stdOutHandle, *seconds);

		Y_LOOP {
			X_LOOP {	
				drawMap(stdOutHandle, i, j, player, 0x2A, ",");
			}
			SetConsoleTextAttribute(stdOutHandle, 0x07);
			printf("\n");
		}

		if (*quarterSecondCounter > 4) {
			*quarterSecondCounter = 0;
			*seconds += 1;
		}

		MovementReturnCode mrc = movement(player, 0, 25, 10, -2);

		Sleep(150);

		if (mrc == EXIT) {
			player->currentSection = EXIT_GAME;
			break;
		}

		if (player->posX <= -1) {
			player->currentSection = SECTION_THREE;
			player->posX = 24;
			player->bg = BG_SAND;
			break;
		} else if (player->posX >= 25) {
			player->currentSection = SECTION_FOUR;
			player->posX = 0;
			break;
		}

		if (player->posY <= -1) {
			player->currentSection = SECTION_FIVE;
			break;
		} else if (player->posY >= 10) {
			player->currentSection = SECTION_ONE;
			player->posY = 0;
			player->bg = BG_CONCRETE;
			break;
		}
	}
}

void sectionThree(Tank *player, HANDLE stdOutHandle, int *quarterSecondCounter, int *seconds) {
	GAME_CLOCK_LOOP {
		COORD redrawPosition = {0,0};
		SetConsoleCursorPosition(stdOutHandle, redrawPosition);

		int i = 0;
		int j = 0;

		int waterLevel = 0;

		drawTopUI(stdOutHandle, *seconds);

		Y_LOOP {
			X_LOOP {
				drawBeachMap(stdOutHandle, i, j, player, 0x6e, waterLevel, ".");
				waterLevel++;
			}
			SetConsoleTextAttribute(stdOutHandle, 0x07);
			printf("\n");
			
			waterLevel = 0;
		}

		if (*quarterSecondCounter > 4) {
			*quarterSecondCounter = 0;
			*seconds += 1;
		}

		MovementReturnCode beachMrc = beachMovement(player, 1, 25, 8, -1);

		Sleep(150);

		if (beachMrc == EXIT) {
			player->currentSection = EXIT_GAME;
			break;
		}

		if (player->posX >= 25) {
			player->currentSection = SECTION_TWO;
			player->posX = 0;
			player->bg = BG_GRASS;
			break;
		}
	}
}

void sectionFour(Tank *player, HANDLE stdOutHandle, int *quarterSecondCounter, int *seconds) {
	GAME_CLOCK_LOOP {
		COORD redrawPosition = {0,0};
		SetConsoleCursorPosition(stdOutHandle, redrawPosition);

		int i = 0;
		int j = 0;

		drawTopUI(stdOutHandle, *seconds);

		Y_LOOP {
			X_LOOP {
				drawMap(stdOutHandle, i, j, player, 0x2A, ",");
			}
			SetConsoleTextAttribute(stdOutHandle, 0x07);
			printf("\n");
		}

		if (*quarterSecondCounter > 4) {
			*quarterSecondCounter = 0;
			*seconds += 1;
		}

		MovementReturnCode mrc = movement(player, 1, 24, 8, -1);

		Sleep(150);

		if (mrc == EXIT) {
			player->currentSection = EXIT_GAME;
			break;
		}

		if (player->posX <= -1) {
			player->currentSection = SECTION_TWO;
			player->posX = 24;
			break;
		} 
	}
}