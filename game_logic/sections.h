#ifndef SECTIONS_H
#define SECTIONS_H

#include <Windows.h>

#include "structs.h"

void sectionOne(Tank *player, HANDLE stdOutHandle, int *quarterSecondCounter, int *seconds);
void sectionTwo(Tank *player, HANDLE stdOutHandle, int *quarterSecondCounter, int *seconds);
void sectionThree(Tank *player, HANDLE stdOutHandle, int *quarterSecondCounter, int *seconds);
void sectionFour(Tank *player, HANDLE stdOutHandle, int *quarterSecondCounter, int *seconds);

#endif