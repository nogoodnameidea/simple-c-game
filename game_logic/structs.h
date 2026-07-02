#ifndef STRUCTS_H
#define STRUCTS_H

#include "enums.h"

typedef struct {
	int posX;
	int posY;
	TankDirection dir;
	TankBackground bg;
	SectionID currentSection;
} Tank;

typedef struct {
	int logPosX;
	int logPosY;
	int leafPosX;
	int leafPosY;
} Tree;

#endif