#ifndef chip8_h
#define chip8_h

#include <cstdint>
#define RAM_SIZE 4096

class chip8{
  private: 
    // uint8_t memory[RAM_SIZE];
  public:
    ///  ------------------- CPU
    uint8_t V[16]; /// register v0-vf
    uint16_t I; // index regester
    uint16_t pc; // program counter 
    uint16_t stack[16];
    uint8_t sp; // stack pointer

    //TIMERS
    uint8_t delayTimer;
    uint8_t soundTimer; 

    int display[64 * 32]; // display frame 
    
    int keypad[16];
  
    bool drawFlag;



};

#endif // !chip8_h
