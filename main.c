#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <mmsystem.h>

typedef enum {
	CONTINUE,
	EXIT
} MovementReturnCode;

typedef enum {
	SECTION_ZERO,
	SECTION_ONE,
	SECTION_TWO,
	SECTION_THREE,
	SECTION_FOUR,
	EXIT_GAME
} SectionID;

typedef enum {
	DIR_UP,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_DOWN
} TankDirection;

typedef enum {
	BG_GRASS,
	BG_SAND,
	BG_CONCRETE
} TankBackground;

typedef struct {
	int posX;
	int posY;
	TankDirection dir;
	TankBackground bg;
	SectionID sectionID;
} Tank;

void drawTopUI(HANDLE stdOutHandle, int time);
void drawTank(HANDLE stdOutHandle, TankDirection tDir, TankBackground tBg);
MovementReturnCode movement(Tank *player, int maxX, int minX, int maxY, int minY);

void sectionZero(Tank *player, HANDLE stdOutHandle, int *quarterSecondCounter, int *seconds);

int main() {
	HANDLE stdOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleOutputCP(CP_UTF8);
	
	Tank player = {
		.posX = 12,
		.posY = 9,
		.dir = DIR_UP,
		.bg = BG_CONCRETE,
		.sectionID = SECTION_ZERO,
	};

	system("cls");
	SetConsoleTextAttribute(stdOutHandle, 0x07);
	printf("Use o zoom para uma melhor experiência");
	Sleep(2000);
	system("cls");


	int quarterSecondCounter = 0;
	int seconds = 0;

	PlaySound("audio/music.wav", NULL, SND_FILENAME | SND_ASYNC);

	switch (player.sectionID) {
		case SECTION_ZERO:
			sectionZero(&player, stdOutHandle, &quarterSecondCounter, &seconds);
			break;
	}

	printf("%d", seconds);
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

void sectionZero(Tank *player, HANDLE stdOutHandle, int *quarterSecondCounter, int *seconds) {
	for (*quarterSecondCounter; *quarterSecondCounter < 1000; *quarterSecondCounter += 1) {
		COORD redrawPosition = {0,0};
		SetConsoleCursorPosition(stdOutHandle, redrawPosition);

		int i = 0;
		int j = 0;


		drawTopUI(stdOutHandle, *seconds);

		for (i; i < 10; i++) {
			for (j = 0; j < 25; j++) {
				SetConsoleTextAttribute(stdOutHandle, 0x87);
				
				if (i == player->posY && j == player->posX) {
					drawTank(stdOutHandle, player->dir, player->bg);
				} else {
					printf(" ");
				}
			}
			SetConsoleTextAttribute(stdOutHandle, 0x07);
			printf("\n");
		}

		if (*quarterSecondCounter > 4) {
			*quarterSecondCounter = 0;
			*seconds += 1;
		}

		MovementReturnCode mrc = movement(player, 1, 24, 8, -2);

		Sleep(150);

		if (mrc == EXIT) {
			player->sectionID = EXIT_GAME;
			break;
		}

		if (player->posY == -2) {
			player->sectionID = SECTION_TWO;
			break;
		}
	}
}

MovementReturnCode movement(Tank *player, int maxX, int minX, int maxY, int minY) {
	if (GetAsyncKeyState('Q') & 0b1) {
		return EXIT;
	}
		
	if ((GetAsyncKeyState(VK_UP) & 0b1) || (GetAsyncKeyState('W') & 0b1)) {
		if (player->posY >= minY) {
			player->posY--;
			player->dir = DIR_UP;
			}
	}

	if ((GetAsyncKeyState(VK_DOWN) & 0b1) || (GetAsyncKeyState('S') & 0b1)) {
		if (player->posY <= maxY) {
			player->posY++;
			player->dir = DIR_DOWN;
		}
	}

	if ((GetAsyncKeyState(VK_LEFT) & 0b1) || (GetAsyncKeyState('A') & 0b1)) {
		if (player->posX >= maxX) {
			player->posX--;
			player->dir = DIR_LEFT;
		}
	}

	if ((GetAsyncKeyState(VK_RIGHT) & 0b1) || (GetAsyncKeyState('D') & 0b1)) {
		if (player->posX <= minX) {
			player->posX++;
			player->dir = DIR_RIGHT;
		}
	}
}
