#ifndef DISPLAY_H
#define DISPLAY_H

#include "chip8.h"
#include <SDL2/SDL.h>

bool init_display(SDL_Window *&window, SDL_Renderer *&renderer);
void render(SDL_Renderer *renderer, Chip8 &chip8);
void close_display(SDL_Window *window, SDL_Renderer *renderer);

#endif