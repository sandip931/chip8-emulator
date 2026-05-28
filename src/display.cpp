#include <iostream>
#include <SDL2/SDL.h>

int main(int argc, char **args)
{
    SDL_Renderer *renderer = NULL;
    SDL_Texture *texture = NULL;
    SDL_Window *window = NULL;
    // checking for initilizing SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Error when initializing SDL" << SDL_GetError();
        system("pause");
        return 1;
    }

    window = SDL_CreateWindow("CHIP-8 Emulator", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 320, SDL_WINDOW_SHOWN);

    if (!window)
    {
        std::cout << "Error creating window" << SDL_GetError() << std::endl;
        system("pause");
        return 1;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (!renderer)
    {
        std::cout << "Error rendering" << SDL_GetError() << std::endl;
        system("pause");
        return 1;
    }
    SDL_Rect pixel = {20, 20, 100, 200};
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 128, 255, 255);
    SDL_RenderFillRect(renderer, &pixel);

    SDL_RenderPresent(renderer);
    system("pause");
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}