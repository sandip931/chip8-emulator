#include "../includes/chip8.h"
#include <cstring>
#include<iostream>



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
        std::memset(display,0,sizeof(display)); // set every px to 0 (off) which means nothing to print in screen = cls 
        drawFlag = true;
      }
      else if (opcode ==0x00EE) { /// return from function 
        pc = stack[--sp]; 
      }
      break;

    case 0x1000:
      pc = addressNNN;
      break;

    case 0x2000:
      stack[sp++] = pc; // store temp address
      pc = addressNNN; //assign addressNNN to pc  //mean:  calling function at address NNN
      break;

    case 0x3000:
      if (V[regX] == valueKK) pc+= 2;
      break;

    case 0x4000:
      if (V[regX] != valueKK) pc+=2;
      break;

    case 0x5000:
      if (V[regX] == V[regY]) pc+=2;
      break;

    case 0x6000:
      V[regX] = valueKK;
      break;

    case 0x7000:
      V[regX]+=valueKK;
      break;

    case 0x8000:

      switch (opcode & 0x000F) {

        case 0x0:// 8xy0 — Copy 
          V[regX]  = V[regY]; 
          V[0xF] = 0; 
          break; 
        case 0x1:// 8xy1 — Bitwise OR 
          V[regX] |= V[regY];
          V[0xF] = 0;
          break; 
        case 0x2: // 8xy2 — Bitwise AND 
          V[regX] &= V[regY];
          V[0xF] = 0; 
          break;
        case 0x3: // 8xy3 — Bitwise XOR 
          V[regX] ^= V[regY];
          V[0xF] = 0;
          break;

        case 0x4:
          {                    // 8xy4 — Math Add with Carry Check
            uint16_t sum = V[regX] + V[regY];
            V[0xF] = (sum > 255) ? 1 : 0;
            V[regX] = sum & 0xFF;
            break;
          }

        case 0x5:
          {                    // 8xy5 — Math Subtract
            uint8_t carry = (V[regX] >= V[regY]) ? 1 : 0;
            V[regX] = V[regX] - V[regY];
            V[0xF] = carry;
            break;
          }

        case 0x6: 
          {                    // 8xy6 — Bit Shift Right
            uint8_t droppedBit = V[regX] & 0x1;
            V[regX] >>= 1;
            V[0xF] = droppedBit;
            break;
          }

        case 0x7: 
          {                    // 8xy7 — Alt Subtract
            uint8_t carry = (V[regY] >= V[regX]) ? 1 : 0;
            V[regX] = V[regY] - V[regX];
            V[0xF] = carry;
            break;
          }

        case 0xE:
          {                    // 8xyE — Bit Shift Left
            uint8_t droppedBit = (V[regX] >> 7) & 0x1;
            V[regX] <<= 1;
            V[0xF] = droppedBit;
            break;
          }
      }
      break;

    case 0x9000:             // 9xy0 — Skip if V[regX] != V[regY]
      if (V[regX] != V[regY]) pc += 2;
      break;

    case 0xA000:           // Annn — Set Index Register I = addressNNN
      I = addressNNN;
      break;


    case 0xB000:          // Bnnn — Jump to addressNNN + V0 register value
      pc = addressNNN + V[0];
      break;

    case 0xC000:
      V[regX] = (rand() % 256) & valueKK;
      break;

    case 0xD000:
      V[0xF] = 0; /// set collision to false  register 
      for(int spriteRow = 0; spriteRow < heightN; spriteRow++){
        uint8_t spriteByte = memory[I + spriteRow]; // extract 1 byte of data from adress I and increase i up to height of sprite
        for(int spriteCol = 0; spriteCol < 8 ; spriteCol++){ // extracting 8 bit from 1 byte  so 0-7 
          if (spriteByte & (0x80 >> spriteCol)) { // extract every 1 bit from a byte
                                                  //
            int px = (V[regX]+spriteCol) % 64; // x-Axis position and wrap to left if out of screenX limit bound  
            int py = (V[regY]+spriteRow) % 32; // similarly for y axis  

            int xyIndex = px + 64 * py; // since our array is linear we cannot write x and y spearately so calculation the total xy value 

            if (display[xyIndex] == 1) V[0xF] = 1; // if there is already a pixel then the collision will be true  
            display[xyIndex] ^= 1; //XORing the pixel and if there is no pixel on in that point of display then only print a pixel there else  turn pixel off
          }
        }
      }
      drawFlag = true;
      break;

    case 0xE000:
      if(valueKK==0x9E){
        if(keypad[V[regX]]){
          pc+=2; /// skip if key is pressed down 
        }
      }
      else if(valueKK==0xA1){
        if(!keypad[V[regX]]){
          pc+=2; // skip if key is up (not pressed) 
        }
      }
      break;

    case 0xF000:
      switch (valueKK) {
        case 0x07: V[regX] = delayTimer; break; 
        case 0x0A: {                      // Fx0A — Wait for a keyboard key block loop
                     bool anyKey = false;
                     for (int k = 0; k < 16; k++) {
                       if (keypad[k]) {
                         V[regX] = k;
                         anyKey = true;
                         break;
                       }
                     }
                     if (!anyKey) pc -= 2; // Loop freeze instruction simulation
                     break;
                   }
        case 0x15: delayTimer = V[regX]; break; 
        case 0x18: soundTimer = V[regX]; break; 
        case 0x1E: I += V[regX]; break;          
        case 0x29: I = V[regX] * 5; break;       // Sets index to point to system font maps
        case 0x33:                            // Fx33 — Binary Coded Decimal breakdown math
                   memory[I]     = V[regX] / 100;
                   memory[I + 1] = (V[regX] / 10) % 10;
                   memory[I + 2] = V[regX] % 10;
                   break;
        case 0x55:                            // Dump internal registers to memory
                   for (int i = 0; i <= regX; i++) memory[I + i] = V[i];
                   break;
        case 0x65:                            // Load internal registers from memory
                   for (int i = 0; i <= regX; i++) V[i] = memory[I + i];
                   break;
      }
      break;

    default:
      std::cerr << "Unrecognized instruction token: " << std::hex << opcode << "\n";
      break;
  }
}






