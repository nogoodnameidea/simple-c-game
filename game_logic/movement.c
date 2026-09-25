#include "enums.h"
#include "macros.h"
#include "movement.h"
#include <stdio.h>

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

	return CONTINUE;
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

	if (MOVE_RIGHT_KEY_PRESSED) {
		if (player->posX <= minX) {
			player->posX++;
			player->dir = DIR_RIGHT;
		}
	}

	return CONTINUE;
}

MovementReturnCode forestMovement(Tank *player, int maxX, int minX, int maxY, int minY) {
	if (QUIT_GAME_KEY_PRESSED) {
		return EXIT;
	}

	Object key = {.posX = 12, .posY = 5};
		
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

	if (player->posX == key.posX && player->posY == key.posY) {
		player->hasKey = 1;
	}

	return CONTINUE;
}

MovementReturnCode gateMovement(Tank *player, int maxX, int minX, int maxY, int minY) {
	if (QUIT_GAME_KEY_PRESSED) {
		return EXIT;
	}
		
	if (MOVE_UP_KEY_PRESSED) {
		if (player->posY <= maxY) {
			if (player->hasKey == 1 && player->posX >= 9 && player->posX <= 13) {
				player->posY--;
				player->dir = DIR_UP;
			} else {
				if (player->posY >= 8) {
					player->posY--;
					player->dir = DIR_UP;
				}		
			}
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

	return CONTINUE;
}