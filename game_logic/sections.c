#include <stdio.h>

#include "macros.h"
#include "movement.h"
#include "sections.h"
#include "structs.h"

#include "../graphics/graphics.h"

void sectionOne(Tank *player, HANDLE stdOutHandle, int *quarterSecondCounter, int *seconds) {
	GAME_CLOCK_LOOP {
		COORD redrawPosition = {0,0};
		SetConsoleCursorPosition(stdOutHandle, redrawPosition);

		int x = 0;
		int y = 0;

		drawTopUI(stdOutHandle, *seconds, *player);

		Y_LOOP {
			X_LOOP {
				drawMap(stdOutHandle, x, y, player, 0x87, " ");
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

		int x = 0;
		int y = 0;


		drawTopUI(stdOutHandle, *seconds, *player);

		Y_LOOP {
			X_LOOP {	
				drawMap(stdOutHandle, x, y, player, 0x2A, ",");
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

		int x = 0;
		int y = 0;

		int waterLevel = 0;

		drawTopUI(stdOutHandle, *seconds, *player);

		Y_LOOP {
			X_LOOP {
				drawBeachMap(stdOutHandle, x, y, player, waterLevel);
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

		MovementReturnCode beachMrc = beachMovement(player, 1, 25, 8, 1);

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

		int x = 0;
		int y = 0;

		drawTopUI(stdOutHandle, *seconds, *player);

		Y_LOOP {
			X_LOOP {
				drawForestMap(stdOutHandle, x, y, player, 0x2A);
			}
			SetConsoleTextAttribute(stdOutHandle, 0x07);
			printf("\n");
		}

		if (*quarterSecondCounter > 4) {
			*quarterSecondCounter = 0;
			*seconds += 1;
		}

		MovementReturnCode mrc = forestMovement(player, 0, 24, 8, 1);

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

void sectionFive(Tank *player, HANDLE stdOutHandle, int *quarterSecondCounter, int *seconds) {
	GAME_CLOCK_LOOP {
		COORD redrawPosition = {0,0};
		SetConsoleCursorPosition(stdOutHandle, redrawPosition);

		int x = 0;
		int y = 0;

		drawTopUI(stdOutHandle, *seconds, *player);

		Y_LOOP {
			X_LOOP {
				drawGateMap(stdOutHandle, x, y, player, 0x2A);
			}
			SetConsoleTextAttribute(stdOutHandle, 0x07);
			printf("\n");
		}

		if (*quarterSecondCounter > 4) {
			*quarterSecondCounter = 0;
			*seconds += 1;
		}

		MovementReturnCode mrc = movement(player, 1, 24, 9, 0);

		Sleep(150);

		if (mrc == EXIT) {
			player->currentSection = EXIT_GAME;
			break;
		}
	}
}