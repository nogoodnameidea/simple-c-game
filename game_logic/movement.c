#include "enums.h"
#include "macros.h"
#include "movement.h"

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
}