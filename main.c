#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef enum {
	DIR_UP,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_DOWN
} TankDirection;

typedef enum {
	BG_GRASS,
	BG_SAND
} TankBackground;

typedef struct {
	int posX;
	int posY;
	TankDirection dir;
	TankBackground bg;
} Tank;

void drawTank(HANDLE stdOutHandle, TankDirection tDir, TankBackground tBg);

int main() {
	HANDLE stdHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleOutputCP(CP_UTF8);
	
	TankDirection tDir = DIR_UP;
	TankBackground tBg = BG_GRASS;

	Tank player = {
		.posX = 12,
		.posY = 9,
		.dir = tDir,
		.bg = tBg
	};

	int spawned = 1;

	system("cls");
	SetConsoleTextAttribute(stdHandle, 0x07);
	printf("Use o zoom para uma melhor experiência");
	Sleep(2000);
	system("cls");

	while (1) {
		COORD redrawPosition = {0,0};
		SetConsoleCursorPosition(stdHandle, redrawPosition);

		int i = 0;
		int j = 0;

		for (i; i < 10; i++) {
			for (j = 0; j < 25; j++) {
				SetConsoleTextAttribute(stdHandle, 0x2A);

				if (i == player.posY && j == player.posX) {
					drawTank(stdHandle, tDir, tBg);
				} else {
					printf(",");
				}
			}
			SetConsoleTextAttribute(stdHandle, 0x07);
			printf("\n");
		}
		
	
		if (GetAsyncKeyState('Q') & 0b1) {
			break;
		}
		
		if ((GetAsyncKeyState(VK_UP) & 0b1) || (GetAsyncKeyState('W') & 0b1)) {
			if (player.posY >= 1) {
				player.posY--;
				tDir = DIR_UP;
				spawned = 0;
			}
		}

		if ((GetAsyncKeyState(VK_DOWN) & 0b1) || (GetAsyncKeyState('S') & 0b1)) {
			if (player.posY <= 8 && spawned != 1) {
				player.posY++;
				tDir = DIR_DOWN;
			}
		}

		if ((GetAsyncKeyState(VK_LEFT) & 0b1) || (GetAsyncKeyState('A') & 0b1)) {
			if (player.posX >= 1) {
				player.posX--;
				tDir = DIR_LEFT;
			}
		}

		if ((GetAsyncKeyState(VK_RIGHT) & 0b1) || (GetAsyncKeyState('D') & 0b1)) {
			if (player.posY <= 24 && spawned != 1) {
				player.posX++;
				tDir = DIR_RIGHT;
			}
		}

		Sleep(150);
	}
	return 0;
}

void drawTank(HANDLE stdOutHandle, TankDirection tDir, TankBackground tBg) {
	switch (tBg) {
		case 1:
			SetConsoleTextAttribute(stdOutHandle, 0x67);
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
