#ifndef MACROS_H
#define MACROS_H

#include <Windows.h>

#define GAME_CLOCK_LOOP for (*quarterSecondCounter; *quarterSecondCounter < 180; *quarterSecondCounter += 1)
#define X_LOOP for (x = 0; x < 25; x++)
#define Y_LOOP for (y; y < 10; y++)

#define QUIT_GAME_KEY_PRESSED GetAsyncKeyState('Q') & 0b1
#define MOVE_UP_KEY_PRESSED (GetAsyncKeyState(VK_UP) & 0b1) || (GetAsyncKeyState('W') & 0b1)
#define MOVE_DOWN_KEY_PRESSED (GetAsyncKeyState(VK_DOWN) & 0b1) || (GetAsyncKeyState('S') & 0b1)
#define MOVE_LEFT_KEY_PRESSED (GetAsyncKeyState(VK_LEFT) & 0b1) || (GetAsyncKeyState('A') & 0b1)
#define MOVE_RIGHT_KEY_PRESSED (GetAsyncKeyState(VK_RIGHT) & 0b1) || (GetAsyncKeyState('D') & 0b1)

#endif