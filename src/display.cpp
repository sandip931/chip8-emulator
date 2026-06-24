#include <iostream>
#include "../includes/display.h"

static const int SCALE = 10;

bool init_display(SDL_Window *&window, SDL_Renderer *&renderer)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
    {
        return false;
        return false;
    }

    window = SDL_CreateWindow("CHIP-8 Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 64 * SCALE, 32 * SCALE, SDL_WINDOW_SHOWN);
    window = SDL_CreateWindow("CHIP-8 Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 64 * SCALE, 32 * SCALE, SDL_WINDOW_SHOWN);
    if (!window)
        return false;
    return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    return renderer != nullptr;
}

void render(SDL_Renderer *renderer, Chip8 &chip8)
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Draw pixel color (White)

    // Translate 1D coordinate state positions to clean 2D squares on screen
    for (int y = 0; y < 32; y++)
    {
        for (int x = 0; x < 64; x++)
        {
            if (chip8.getDisplay(y * 64 + x) == 1)
            {
                SDL_Rect block = {x * SCALE, y * SCALE, SCALE, SCALE};
                SDL_RenderFillRect(renderer, &block);
            }
        }
    }

    SDL_RenderPresent(renderer);
    chip8.setDrawFlag(false);
}

void close_display(SDL_Window *window, SDL_Renderer *renderer)
{

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}