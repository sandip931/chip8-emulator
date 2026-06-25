#include "../includes/display.h"
#include <iostream>

static const int SCALE = 10;
static SDL_AudioDeviceID audioDevice = 0;
static bool audioPlaying = false;

// display initilization  // check for errors 
bool initDisplay(SDL_Window*& window, SDL_Renderer*& renderer) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0) {
        return false;
    }

    window = SDL_CreateWindow(
        "CHIP-8 Engine",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        64 * SCALE,
        32 * SCALE,
        SDL_WINDOW_SHOWN
    );

    if (!window) return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    return renderer != nullptr;
}

// rendering code ..  rectangle
void render(SDL_Renderer* renderer, Chip8& chip8) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 0, 128, 0, 1);

    for (int y = 0; y < 32; y++) {
        for (int x = 0; x < 64; x++) {
            if (chip8.getDisplay(y * 64 + x) == 1) {
                SDL_Rect block = { x * SCALE, y * SCALE, SCALE, SCALE };
                SDL_RenderFillRect(renderer, &block);
            }
        }
    }

    SDL_RenderPresent(renderer);
    chip8.setDrawFlag(false);
}

void closeDisplay(SDL_Window* window, SDL_Renderer* renderer) {
    if (audioDevice != 0) SDL_CloseAudioDevice(audioDevice);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

static void audioCallback(void* userdata, Uint8* stream, int len) {
    static int sampleIndex = 0;

    int16_t* outputBuffer = (int16_t*)stream;
    int sampleCount = len / 2;

    for (int i = 0; i < sampleCount; i++) {
        if ((sampleIndex % 100) < 50) {
            outputBuffer[i] = 8000;
        } else {
            outputBuffer[i] = -8000;
        }
        sampleIndex++;
    }
}

void playBeep() {
    if (audioDevice == 0) {
        SDL_AudioSpec setup;
        SDL_memset(&setup, 0, sizeof(setup));

        setup.freq = 44100;
        setup.format = AUDIO_S16SYS;
        setup.channels = 1;
        setup.samples = 512;
        setup.callback = audioCallback;

        audioDevice = SDL_OpenAudioDevice(nullptr, 0, &setup, nullptr, 0);
    }

    if (!audioPlaying && audioDevice != 0) {
        SDL_PauseAudioDevice(audioDevice, 0);
        audioPlaying = true;
    }
}

void stopBeep() {
    if (audioDevice != 0 && audioPlaying) {
        SDL_PauseAudioDevice(audioDevice, 1);
        audioPlaying = false;
    }
}
