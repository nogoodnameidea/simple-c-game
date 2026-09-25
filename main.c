#include <Windows.h>

#include "game_logic/enums.h"
#include "game_logic/macros.h"
#include "game_logic/movement.h"
#include "game_logic/sections.h"
#include "game_logic/structs.h"

#include "graphics/graphics.h"

#include "audio/music.h"

int main() {
	HANDLE stdOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleOutputCP(CP_UTF8);
	
	Tank player = {
		.posX = 12,
		.posY = 9,
		.dir = DIR_UP,
		.bg = BG_CONCRETE,
		.currentSection = SECTION_ONE,
		.hasKey = 0,
	};

	int quarterSecondCounter = 0;
	int seconds = 0;

	int isRunning = 1;

	HANDLE musicThread = CreateThread(NULL, 0, music_player, NULL, 0, NULL);

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
			case SECTION_FIVE:
				sectionFive(&player, stdOutHandle, &quarterSecondCounter, &seconds);
				break;
			case END_GAME:
				endGameText(&player);
			default:
				isRunning = 0;
				CloseHandle(stdOutHandle);
				CloseHandle(musicThread);
				break;
		}
	}

	return 0;
}