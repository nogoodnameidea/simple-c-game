#ifndef LOADFILE
#define LOADFILE

#include <stdint.h>

int loadFile(const char* filename, void** data, uint32_t* numBytesRead);
void freeFileData(void* data);

#endif