#ifndef MOVEMENT_H
#define MOVEMENT_H

#include "structs.h"

MovementReturnCode movement(Tank *player, int maxX, int minX, int maxY, int minY);
MovementReturnCode beachMovement(Tank *player, int maxX, int minX, int maxY, int minY);
MovementReturnCode forestMovement(Tank *player, int maxX, int minX, int maxY, int minY);

#endif