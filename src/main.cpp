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
    std::cerr <<RED
      <<"[ ERROR ! ] : " 
      <<RESET<<"Invalid number of arguments.\n"

      <<YELLOW
      <<"[ HINT ] :"
      <<RESET<<" you may have forgotten to provide input fileName (.ch8).\n"

      <<GREEN
      <<"[ USAGE ] : \n"
      <<RESET
      <<"-----------------------------------\n"
      <<"chip8  < .ch8_filePath > \n"
      <<"OR \n./chip8 < .ch8_filePath >\n"
      <<"-----------------------------------\n";

    return 1;
  }

  srand(static_cast<unsigned int>(time(nullptr))); // random seed for game


  Chip8 chip8;

  // ROM loading check for errors 
  if(!chip8.loadRom(argv[1])){
    return 1;
  }

  const int cyclesPerFrame = 8;
  const int targetFPS = 60;
  const int frameDelayMS = 1000/ targetFPS; // around 480hz

  bool running = true;  // gameloop conditional variable 

  //// main GameLoop
  while(running){

  }
  // chip8.systemStatus(chip8); // log  planned TO-DO last
  return 0;
}
