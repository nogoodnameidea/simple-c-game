#ifndef PARSE_FILE
#define PARSE_FILE

#include <stdint.h>

typedef struct {
    uint32_t numChannels;
    uint32_t numBitsPerSample;
    uint32_t sampleRate;
    uint32_t numSamples;
    void* samples;
} AudioClip;

AudioClip parseWav(uint8_t *fileBytes, uint32_t fileSize);

#endif