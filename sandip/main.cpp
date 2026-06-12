#include<SDL2/SDL.h>
#include<iostream>
#define main SDL_main
/// sdl window initilization and RENDERING RECTANGLE  ... practice test  

void init(SDL_Window *&window, SDL_Renderer *&renderer)
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
        std::cout << "not working"; //

    window = SDL_CreateWindow("new win ", 0, 0, 300, 400, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_WINDOW_SHOWN); // rendering instance

    if (!window)
        std::cout << "not working";
    if (!renderer)
        std::cout << "not";
};
void rendering(SDL_Renderer *&renderer,SDL_Rect& x) {
    SDL_RenderClear(renderer);                          // garbage clear
    SDL_SetRenderDrawColor(renderer, 200, 155, 20, 90); // obj color
    SDL_RenderFillRect(renderer, &x);

    SDL_RenderPresent(renderer);
};
void cleanup(){

};

int main(int argc, char *argv[])
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Rect x = {2, 3, 15, 15};

    init(window, renderer);

    rendering(renderer, x);

  
    SDL_DestroyWindow(window);

    SDL_Quit();
    return 0;
}
