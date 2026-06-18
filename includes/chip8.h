#ifndef chip8_h
#define chip8_h

#include <cstdint>
#define RAM_SIZE 4096

class Chip8{
  public:
    ///  ------------------- CPU Architecture --------
   
    uint8_t memory[RAM_SIZE];  // 4kb memory 
    uint8_t V[16]; /// register v0-vf
    uint16_t I; // index regester
    uint16_t pc; // program counter 
    uint16_t stack[16]; // stores temp mem address for jumping and subroutine 
    uint8_t sp; // stack pointer

    //------------------- TIMERS
    uint8_t delayTimer;
    uint8_t soundTimer; 

    uint8_t display[64 * 32]; // display frame 
    uint8_t keypad[16];  // 0 - F 
  
    bool drawFlag;

    Chip8(); // default constructor
    bool loadRom();
    void cycle();
    void updateTimers();

    bool getDrawFlag(); // true (for draw) else false 
    void setDrawFlag(bool value);  
    int  getDisplay(int index); // return position of the index -> (x,y)
    void setKey(int key, int val); // setKey 0-F 
    bool soundActive(); // if true beep sound activates 
};

#endif