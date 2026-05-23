#ifndef chip8_h
#define chip8_h

#include <cstdint>
#define RAM_SIZE 4096

class chip8{
  private: 
    // uint8_t memory[RAM_SIZE];
  public:
    uint8_t V[16];
    uint16_t I;

    uint16_t stack[16];
    uint8_t sp;

    uint8_t delayTimer;
    uint8_t soundTimer;

    uint8_t display[64 * 32];

    bool keys[16];

    bool drawFlag;

    uint16_t pc;


};

#endif // !chip8_h
