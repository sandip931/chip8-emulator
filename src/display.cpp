#include <iostream>
#include <SDL2/SDL.h>

int main(int argc, char **args)
{

    SDL_Surface *winSurface = NULL;
    SDL_Window *window = NULL;
    // checking for initilizing SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Error when initializing SDL";
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

    winSurface = SDL_GetWindowSurface(window);

    if (!winSurface)
    {
        std::cout << "Error getting surface" << SDL_GetError() << std::endl;
        system("pause");
        return 1;
    }

    SDL_FillRect(winSurface, NULL, SDL_MapRGB(winSurface->format, 255, 255, 255));

    SDL_UpdateWindowSurface(window);
    system("pause");

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}