#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <Windows.h>

#include "../game_logic/enums.h"
#include "../game_logic/structs.h"

void drawTopUI(HANDLE stdOutHandle, int time);
void drawTank(HANDLE stdOutHandle, TankDirection tDir, TankBackground tBg);
void drawMap(HANDLE stdOutHandle, int mapPosX, int mapPosY, Tank *player, int bgColor, char *tileCharacter);
void drawBeachMap(HANDLE stdOutHandle, int mapPosX, int mapPosY, Tank *player, int bgColor, int waterLevel, char *tileCharacter);
void drawForestMap(HANDLE stdOutHandle, int mapPosX, int mapPosY, Tank *player, int bgColor, Tree trees[5]);

#endif