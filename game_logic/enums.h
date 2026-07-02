#ifndef ENUMS_H
#define ENUMS_H

typedef enum {
	CONTINUE,
	EXIT
} MovementReturnCode;

typedef enum {
	SECTION_ONE,
	SECTION_TWO,
	SECTION_THREE,
	SECTION_FOUR,
	SECTION_FIVE,
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

#endif