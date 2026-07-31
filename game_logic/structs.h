#ifndef STRUCTS_H
#define STRUCTS_H

#include "enums.h"

typedef struct {
	int posX;
	int posY;
	TankDirection dir;
	TankBackground bg;
	SectionID currentSection;
	int hasKey;
} Tank;

#endif