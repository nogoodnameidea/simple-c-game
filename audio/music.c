#include "music.h"
#include <mmsystem.h>

DWORD WINAPI music_player(LPVOID arg) {
    PlaySound("audio/music.wav", NULL, SND_FILENAME | SND_SYNC);
    PlaySound("audio/music_loop.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

    return 0;
}