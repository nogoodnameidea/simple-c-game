#include <stdio.h>
#include <Windows.h>
#include <initguid.h>
#include <Audioclient.h>
#include <mmdeviceapi.h>

#include "loadfile.h"
#include "parsefile.h"

DWORD WINAPI music_player(LPVOID arg) {
    const char* wavFilename = "audio/music.wav";
    void* fileBytes;
    uint32_t fileSize;
    int result = loadFile(wavFilename, &fileBytes, &fileSize);

    AudioClip clip = parseWav((uint8_t*)fileBytes, fileSize);
    HRESULT hr = CoInitializeEx(NULL, COINIT_SPEED_OVER_MEMORY);
    IMMDeviceEnumerator *enumerator = NULL;

    hr = CoCreateInstance(
        &CLSID_MMDeviceEnumerator,
        NULL,
        CLSCTX_ALL,
        &IID_IMMDeviceEnumerator,
        (void**)&enumerator
    );

    IMMDevice* renderer = NULL;

    hr = enumerator->lpVtbl->GetDefaultAudioEndpoint(enumerator, eRender, eConsole, &renderer);

    hr = enumerator->lpVtbl->Release(enumerator);

    IAudioClient *renderClient = NULL;

    hr = renderer->lpVtbl->Activate(renderer, &IID_IAudioClient, CLSCTX_ALL, NULL, (void**)&renderClient);

    const int32_t OUTPUT_SAMPLE_RATE = 44100;
    WAVEFORMATEX format = {};
    format.wFormatTag = WAVE_FORMAT_PCM;
    format.nChannels = 2;
    format.nSamplesPerSec = OUTPUT_SAMPLE_RATE;
    format.wBitsPerSample = 16;
    format.nBlockAlign = (format.nChannels * format.wBitsPerSample) / 8;
    format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign;

    const float BUFFER_SIZE_IN_SECONDS = 2.0f;
    const int64_t REFTIMES_PER_SEC = 10000000;

    DWORD initStreamFlags = (AUDCLNT_STREAMFLAGS_RATEADJUST | AUDCLNT_STREAMFLAGS_AUTOCONVERTPCM | AUDCLNT_STREAMFLAGS_SRC_DEFAULT_QUALITY);
    REFERENCE_TIME requestedSoundBufferDuration = (REFERENCE_TIME)(REFTIMES_PER_SEC * BUFFER_SIZE_IN_SECONDS);

    hr = renderClient->lpVtbl->Initialize(renderClient, AUDCLNT_SHAREMODE_SHARED, initStreamFlags, requestedSoundBufferDuration, 0, &format, NULL);

    IAudioRenderClient *renderService = NULL;

    hr = renderClient->lpVtbl->GetService(renderClient, &IID_IAudioRenderClient, (void**)&renderService);

    UINT32 nFrames;
    DWORD flags;
    BYTE *renderBuffer;

    UINT32 bufferSizeInFrames; // Tenho minhas dúvidas sobre o tipo
    hr = renderClient->lpVtbl->GetBufferSize(renderClient, &bufferSizeInFrames);

    hr = renderClient->lpVtbl->Start(renderClient);

    uint32_t wavPlaybackSample = 0;
    uint32_t loopPlaybackSample = 176047;
    while (1) {
        UINT32 bufferPadding;
        hr = renderClient->lpVtbl->GetCurrentPadding(renderClient, &bufferPadding);

        const float TARGET_BUFFER_PADDING_IN_SECONDS = 1 / 60.f;
        UINT32 targetBufferPadding = (UINT32)bufferSizeInFrames * TARGET_BUFFER_PADDING_IN_SECONDS;
        UINT32 numFramesToWrite = targetBufferPadding - bufferPadding;

        int16_t *buffer;
        hr = renderService->lpVtbl->GetBuffer(renderService, numFramesToWrite, (BYTE**)(&buffer));

        for(UINT32 frameIndex = 0; frameIndex < numFramesToWrite; ++frameIndex)
        {
            uint32_t leftSampleIndex = wavPlaybackSample;
            uint32_t rightSampleIndex = wavPlaybackSample + clip.numChannels - 1;
            *buffer++ = ((uint16_t*)clip.samples)[leftSampleIndex];
            *buffer++ = ((uint16_t*)clip.samples)[rightSampleIndex];
            wavPlaybackSample += clip.numChannels;
            if (wavPlaybackSample >= clip.numSamples) {
                wavPlaybackSample = loopPlaybackSample;
            }
        }
        hr = renderService->lpVtbl->ReleaseBuffer(renderService, numFramesToWrite, 0);
    }

    renderClient->lpVtbl->Stop(renderClient);
    renderClient->lpVtbl->Release(renderClient);

    freeFileData(fileBytes);

    CoUninitialize();
    return 0;
}