#include <stdio.h>
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <mmsystem.h>
#include <aviriff.h>

#include "parsefile.h"

AudioClip parseWav(uint8_t *fileBytes, uint32_t fileSize) {
    AudioClip result = {};

    RIFFLIST *header = (RIFFLIST*)fileBytes;

    if(header->fcc != FCC('RIFF') || header->fccListType != FCC('WAVE'))
    {
        printf("HEADER INVÁLIDO!\n");
        return result;
    }

    void* subChunks = fileBytes + sizeof(RIFFLIST);
    void* endOfFile = fileBytes + fileSize;

    for(RIFFCHUNK* chunk = (RIFFCHUNK*)(subChunks); chunk < endOfFile; chunk = RIFFNEXT(chunk))
    {
        if(chunk->fcc == FCC('fmt '))
        {
            WAVEFORMATEX* fmt = (WAVEFORMATEX*)(chunk + 1);

            if(fmt->wFormatTag != WAVE_FORMAT_PCM)
            {
                printf("FORMATO NÃO SUPORTADO!\n");
                return result;
            }

            result.numChannels = fmt->nChannels;
            result.sampleRate = fmt->nSamplesPerSec;
            result.numBitsPerSample = fmt->wBitsPerSample;
        }
        else if(chunk->fcc == FCC('data'))
        {
            result.numSamples = chunk->cb / sizeof(uint16_t);
            result.samples = ((uint8_t*)chunk + sizeof(RIFFCHUNK));
        }
    }
    return result;
}