#include "../includes/chip8.h"
#include <cstring>

void Chip8::updateTimers()
{
  if (delayTimer > 0)
    delayTimer--;
  if (soundTimer > 0)
    soundTimer--;
}

void Chip8::cycle()
{
  uint16_t opcode = (memory[pc] << 8) | memory[pc + 1];
  pc += 2;

  uint8_t regX = (opcode & 0x0F00) >> 8; // Vx
  uint8_t regY = (opcode & 0x00F0) >> 4; // Vy
  uint8_t valueKK = opcode & 0x00FF;     // constant
  uint16_t addressNNN = opcode & 0x0FFF; // 12 bits (address)
  uint8_t heightN = opcode & 0x000F;     // lowest nibble

  // to decode:
  switch (opcode & 0xF000)
  {
    // check opcode family and specific ops
  case 0x0000:
    if (opcode == 0x00E0)
    {                                           // CLEAR SCREEN
      std::memset(display, 0, sizeof(display)); // set every px to 0 (off) which means nothing to print in screen = cls
    }
    else if (opcode == 0x00EE)
    { /// return from function
      pc = stack[--sp];
    }
    break;

  case 0x1000:
    // rgr
    break;

  case 0x2000:
    stack[sp++] = pc; // store temp address
    pc = addressNNN;  // assign addressNNN to pc  //mean:  calling function at address NNN
    break;

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
    V[regX] += valueKK;
    break;

  case 0x8000:
    switch (opcode & 0x000F)
    {
    case 0x0:
      V[regX] = V[regY];
      V[0xF] = 0;
      break; // 8xy0 Copy
    case 0x1:
      V[regX] |= V[regY];
      V[0xF] = 0;
      break; // 8xy1 Bitwise OR
    case 0x2:
      V[regX] &= V[regY];
      V[0xF] = 0;
      break; // 8xy2 Bitwise AND
    case 0x3:
      V[regX] ^= V[regY];
      V[0xF] = 0;
      break; // 8xy3 Bitwise XOR
    }
    break;

  case 0x9000:
    if (V[regX] != V[regY])
      pc += 2; // skips if V[regX] != V[regY]
    break;

  case 0xA000:
    I = addressNNN;
    break;

  case 0xB000:
    pc = addressNNN + V[0];
    break;

  case 0xC000:
    // roger

    break;

  case 0xD000:
    V[0xF] = 0; /// set collision to false  register
    for (int spriteRow = 0; spriteRow < heightN; spriteRow++)
    {
      uint8_t spriteByte = memory[I + spriteRow]; // extract 1 byte of data from adress I and increase i up to height of sprite
      for (int spriteCol = 0; spriteCol < 8; spriteCol++)
      { // extracting 8 bit from 1 byte  so 0-7
        if (spriteByte & (0x80 >> spriteCol))
        {                                      // extract every 1 bit from a byte
                                               //
          int px = (V[regX] + spriteCol) % 64; // x-Axis position and wrap to left if out of screenX limit bound
          int py = (V[regY] + spriteRow) % 32; // similarly for y axis

          int xyIndex = px + 64 * py; // since our array is linear we cannot write x and y spearately so calculation the total xy value

          if (display[xyIndex] == 1)
            V[0xF] = 1;          // if there is already a pixel then the collision will be true
          display[xyIndex] ^= 1; // XORing the pixel and if there is no pixel on in that point of display then only print a pixel there else  turn pixel off
        }
      }
    }
    break;

  case 0xE000:
    if (valueKK == 0x9E)
    {
      if (keypad[V[regX]])
      {
        pc += 2; /// skip if key is pressed down
      }
    }
    else if (valueKK == 0xA1)
    {
      if (!keypad[V[regX]])
      {
        pc += 2; // skip if key is up (not pressed)
      }
    }
    break;

  case 0xF000:
  case 0x07:
    V[regX] = delayTimer;
    break;
  case 0x0A:
    // prashant
    break;
  case 0x15:
    delayTimer = V[regX];
    break;
  case 0x18:
    soundTimer = V[regX];
    break;
  case 0x1E: // prashant's from here
    break;
  }
}
