#ifndef chip8_h
#define chip8_h

#include <cstdint>
#include <string>

#define RAM_SIZE 4096

class Chip8{
  private: 
    uint8_t memory[RAM_SIZE];

    ///  ------------------- CPU
    uint8_t V[16]; /// register v0-vf
    uint16_t I; // index regester
    uint16_t pc; // program counter 
    uint16_t stack[16];
    uint8_t sp; // stack pointer

    //TIMERS
    uint8_t delay_timer;
    uint8_t sound_timer; 

    int display[64 * 32];
    
    int keypad[16];
  
    bool drawFlag;
  public:

    Chip8();
    bool load_rom(std::string path);
    void cycle();
    void update_timers();
};

#endif // !chip8_h
