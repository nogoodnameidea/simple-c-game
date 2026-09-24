#include "loadfile.h"

#include <Windows.h>

int loadFile(const char* filename, void** data, uint32_t* numBytesRead)
{
    HANDLE file = CreateFileA(filename, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
    if((file == INVALID_HANDLE_VALUE)) return 1;

    DWORD fileSize = GetFileSize(file, 0);
    if(!fileSize) return 1;

    *data = HeapAlloc(GetProcessHeap(), 0, fileSize + 1);
    if(!*data) return 1;

    if(!ReadFile(file, *data, fileSize, (LPDWORD)numBytesRead, 0)) return 1;

    CloseHandle(file);
    ((uint8_t*)*data)[fileSize] = 1;

    return 0;
}

void freeFileData(void* data)
{
    HeapFree(GetProcessHeap(), 0, data);
}