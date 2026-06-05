#include "../includes/chip8.h"


void Chip8::update_timers() {
    if (delay_timer > 0) delay_timer--;
    if (sound_timer > 0) sound_timer--;
}


void Chip8::cycle() {
   uint16_t opcode = (memory[pc] << 8) | memory[pc + 1];
    pc += 2;
    

    uint8_t  x   = (opcode & 0x0F00) >> 8;  // Vx
    uint8_t  y   = (opcode & 0x00F0) >> 4;  // Vy
    uint8_t  kk  =  opcode & 0x00FF;        // constant
    uint16_t nnn =  opcode & 0x0FFF;        // 12 bits (address)
    uint8_t  n   =  opcode & 0x000F;        // lowest nibble
    
// to decode:
    switch (opcode & 0xF000) {
     //check opcode family and specific ops
     //my part: 1nnn, 3xkk, 4xkk, 5xy0, 6xkk, 7xkk, 8xy4, 8xy5, 8xy6, 8xy7, 8xyE, Cxkk
    }
}
