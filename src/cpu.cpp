#include "../includes/chip8.h"
#include <cstring>


void Chip8::updateTimers() {
    if (delayTimer > 0) delayTimer--;
    if (soundTimer > 0) soundTimer--;
}


void Chip8::cycle() {
   uint16_t opcode = (memory[pc] << 8) | memory[pc + 1];
    pc += 2;
    

    uint8_t  regX   = (opcode & 0x0F00) >> 8;  // Vx
    uint8_t  regY   = (opcode & 0x00F0) >> 4;  // Vy
    uint8_t  valueKK  =  opcode & 0x00FF;        // constant
    uint16_t addressNNN =  opcode & 0x0FFF;        // 12 bits (address)
    uint8_t  heightN   =  opcode & 0x000F;        // lowest nibble
    
// to decode:
    switch (opcode & 0xF000) {
     //check opcode family and specific ops
      case 0x0000:
        if(opcode == 0x00E0){ // CLEAR SCREEN
          std::memset(display,0,sizeof(display)); // set every px to 0 (off) which means nothing to pring in screen = cls 
        }
        else if (opcode ==0x00EE) { /// return from function 
          pc = stack[--sp]; 
        }
        //sandip
      break;

      case 0x1000:
        //rgr
      break;

      case 0x2000:
        //sandip
      break;

      // from 0x3000 t0 0x8000 roger part
      case 0x3000:

      break;

      case 0x4000:
        
      break;

      case 0x5000:

      break;

      case 0x6000:

      break;

      case 0x7000:

      break;

      case 0x8000:
        switch (opcode & 0x000F) {
        
        }
      break;
        //aadarsha
      case 0x9000:

      break;

      case 0xA000:
       //aadarsha 
      break;

      case 0xB000:
       //aadarsha 
      break;

      case 0xC000:
        //roger

      break;

      case 0xD000:
        //sandip

      break;

      case 0xE000:
        //sandip

      break;

      case 0xF000:
        //prashant
      break;
    }
}
