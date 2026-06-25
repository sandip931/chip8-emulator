#include "../includes/chip8.h"
#include "../includes/display.h"
#include "../includes/memory.h"
#include <cstdlib>
#include <ctime>
#include<iostream>

//// defined colors for error message 
#define RED     "\033[31m" // ERROR
#define YELLOW  "\033[33m" // HINT
#define GREEN   "\033[32m" // USAGE
#define RESET   "\033[0m" // default WHITE


int main(int argc, char* argv[]){

  // Argument handeling and usage msg  
  if(argc !=2){
    SDL_Init(0);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR,
        "Usage Error",
        "Usage: chip8 <path_to_rom>\nExample: chip8 ../roms/pong.ch8",
        nullptr);
    return 1;
  }

  srand(static_cast<unsigned int>(time(nullptr))); // random seed for game


  Chip8 chip8;

  // ROM loading check for errors 
  if(!chip8.loadRom(argv[1])){
    return 1;
  }

  SDL_Window* window   = nullptr;
  SDL_Renderer* renderer = nullptr;

  if (!initDisplay(window, renderer)) {
    return 1;
  }

  const int cyclesPerFrame = 8;
  const int targetFPS = 60;
  const int frameDelayMS = 1000/ targetFPS; // around 480hz

  bool running = true;  // gameloop conditional variable 

  //// main GameLoop
  while(running){
    Uint32 frameStart = SDL_GetTicks();

    // input handeling and eventHandler
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
      if (e.type == SDL_QUIT) running = false;
      handleInput(chip8, e); 
    }

    /// cpu core logic from cpu.h single cycle for 8 times  
    for (int i = 0; i < cyclesPerFrame; i++) {
      chip8.cycle();   
    }
    chip8.updateTimers();

    // rendering only if drawflag is true 
    if (chip8.getDrawFlag()) {
      render(renderer, chip8); 
    }

    // beep sound on / off
    if (chip8.soundActive()) {
      playBeep();
    } else {
      stopBeep();
    }

    /// frame delay for pacing 
    Uint32 frameTime = SDL_GetTicks() - frameStart;
    if (frameTime <static_cast<Uint32>(frameDelayMS)) {
      SDL_Delay(frameDelayMS - frameTime);
    }

    ///// LOG DEBUG PANNEL 
    // chip8.systemStatus(chip8); // log  planned TO-DO 
  }

  closeDisplay(window, renderer);

  return 0;
}
