# chip8-emulator

A CHIP-8 virtual machine written in C++, using SDL2 for graphics, audio, and keyboard input.

## What is CHIP-8

CHIP-8 is an interpreted programming language and virtual machine created in the mid-1970s by Joseph Weisbecker for the COSMAC VIP and Telmac 1800 microcomputers. It was never a real physical CPU. Instead, programs were written directly as CHIP-8 bytecode and run through an interpreter, which made it possible to write simple games without hand-writing native machine code for each different computer.

Because the machine is so small, CHIP-8 has become one of the most common starting projects for people learning how emulators and interpreters work. A typical CHIP-8 system has the following characteristics:

- 4096 bytes (4 KB) of memory, with programs conventionally loaded starting at address `0x200`
- 16 general purpose 8-bit registers, `V0` through `VF`, where `VF` often doubles as a flag register for carry, borrow, and collision
- A 16-bit index register `I`, mainly used to point at memory for sprite drawing
- A 16-bit program counter and a stack (traditionally 16 levels deep) used for subroutine calls
- Two 8-bit timers, a delay timer and a sound timer, both counting down at 60 Hz
- A 64x32 pixel monochrome display, where each pixel is drawn or erased using XOR logic
- A 16-key hexadecimal keypad, labeled `0` through `F`
- 35 opcodes, each 2 bytes wide, covering jumps, arithmetic, conditional skips, drawing, and register/memory transfers

This repository implements that machine and pairs it with an SDL2 front end so ROM files can actually be seen and played.

## Repository structure

```
chip8-emulator/
├── includes/
│   ├── chip8.h      # Chip8 class definition: registers, memory, stack, timers, display, keypad
│   ├── cpu.h         # currently empty
│   ├── display.h     # SDL2 window/renderer/audio function declarations
│   └── memory.h      # input-handling function declaration
├── src/
│   ├── chip8.cpp     # currently empty
│   ├── cpu.cpp        # opcode fetch-decode-execute cycle and timer updates
│   ├── display.cpp    # SDL2 window setup, pixel rendering, and beep audio
│   ├── main.cpp        # program entry point and the main emulation loop
│   └── memory.cpp     # Chip8 constructor, font data, ROM loading, keyboard mapping
├── roms/
│   └── PONG.ch8       # a sample ROM to test the emulator with
├── Makefile
├── resources.md       # reference material used while building this
└── .gitignore
```

### How the pieces connect

`includes/chip8.h` declares the `Chip8` class, which is the entire state of the virtual machine: its memory array, its 16 registers, the index register and program counter, the stack, the two timers, the display buffer, and the keypad state. Every other file operates on this one class rather than holding separate global state.

`src/memory.cpp` implements the `Chip8` constructor. It zeroes out memory, registers, the display, and the keypad, sets the program counter to `0x200`, and copies a built-in 80-byte font set (five bytes per hexadecimal character, `0` through `F`) into the first bytes of memory so that sprite-drawing opcodes for text have something to point at. The same file implements `loadRom()`, which reads a ROM file from disk into memory starting at `0x200`, and `handleInput()`, which translates SDL keyboard events into the emulator's 16-key keypad state using a fixed key map.

`src/cpu.cpp` implements `Chip8::cycle()`, which is the actual interpreter. On every call it reads two bytes from memory at the program counter to form a 16-bit opcode, advances the program counter by two, and then decodes and executes that instruction through a switch statement covering all standard CHIP-8 opcodes: screen clearing, subroutine calls and returns, jumps, conditional skips, register arithmetic, bitwise operations, the sprite-drawing instruction, keypad checks, and the timer, BCD, and memory transfer instructions grouped under the `F` opcode family. The same file implements `updateTimers()`, which counts the delay and sound timers down once they are non-zero.

`includes/display.h` and `src/display.cpp` are the SDL2 front end. `initDisplay()` opens an SDL window and an accelerated renderer sized to the 64x32 CHIP-8 screen scaled up by a factor of 10. `render()` reads the emulator's display buffer and draws each active pixel as a filled rectangle, then clears the emulator's internal draw flag. `playBeep()` and `stopBeep()` open an SDL audio device on first use and generate a simple square wave tone while the sound timer is active.

`src/main.cpp` ties everything together. It checks that a ROM path was passed on the command line, seeds the random number generator (used by the CHIP-8 `RND` instruction), constructs a `Chip8` instance, loads the ROM, opens the SDL window, and then runs the main loop: poll input, run several CPU cycles, count down the timers, render if something changed, update the beep, and pace the loop to roughly 60 frames per second.

`includes/cpu.h` and `src/chip8.cpp` currently contain no code. They exist as placeholders in the project layout but nothing includes or compiles against them yet.

## Requirements

- A C++ compiler with C++11 support or later (the project is built and tested with g++/MinGW)
- SDL2 development libraries, including the SDL2 headers and `SDL2main`
- `make`

The Makefile as written targets a Windows/MinGW toolchain: it links against `mingw32` and passes `-mwindows`, and the `builddir` and `clean` targets use Windows batch commands (`if not exist`, `del`). Building on Windows through MSYS2/MinGW with SDL2 installed will work with the Makefile as is. On Linux or macOS, install the SDL2 development package for your platform (for example `libsdl2-dev` on Debian/Ubuntu, or `SDL2` from Homebrew on macOS) and compile directly instead of relying on the Windows-specific parts of the Makefile:

```sh
g++ -Iincludes -g src/*.cpp -o build/chip8 $(sdl2-config --cflags --libs)
```

## Building on Windows

```sh
make
```

This creates `build/game.exe`. To build and immediately run against a ROM in one step:

```sh
make run
```

To remove the build output:

```sh
make clean
```

## Running

The emulator takes exactly one argument: the path to a CHIP-8 ROM file.

```sh
./build/game.exe roms/PONG.ch8
```

Running it with the wrong number of arguments pops up an SDL message box explaining correct usage instead of crashing silently.

## Controls

The original CHIP-8 keypad had 16 keys laid out in a 4x4 grid. This emulator maps that layout onto the left side of a standard QWERTY keyboard:

| CHIP-8 key | 1 | 2 | 3 | C | 4 | 5 | 6 | D | 7 | 8 | 9 | E | A | 0 | B | F |
|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
| Keyboard   | 1 | 2 | 3 | 4 | Q | W | E | R | A | S | D | F | Z | X | C | V |

## ROMs

The `roms/` folder currently includes `PONG.ch8` as a sample program to confirm the emulator runs correctly. Any standard CHIP-8 ROM file can be pointed to at the command line; a wide range of public domain CHIP-8 programs and games are available from various community archives, several of which are linked in `resources.md`.

## Implementation notes

A few behaviors are worth knowing if you plan to read the opcode table or extend it:

- The logical operations `8XY1` (OR), `8XY2` (AND), and `8XY3` (XOR) reset `VF` to `0` after executing. Some original CHIP-8 interpreters left `VF` untouched by these instructions; this implementation follows the more commonly used modern convention.
- `FX55` and `FX65` (register dump and load) do not modify the index register `I` afterward. The original COSMAC VIP interpreter incremented `I` as a side effect of these instructions; many modern CHIP-8 programs assume it does not, which is the behavior implemented here.
- Sprite drawing (`DXYN`) wraps pixels around the edges of the screen using modulo arithmetic on the x and y coordinates rather than clipping them.
- `FX0A` (wait for a key press) is implemented by decrementing the program counter by two whenever no key is currently held, which causes the same instruction to be re-fetched and re-executed on the next cycle until a key is pressed. This blocks program execution but still allows the frame loop, rendering, and timers to keep running.
- The CPU runs 8 cycles per rendered frame at a target of 60 frames per second, which works out to roughly 480 instructions per second. The delay and sound timers are only decremented once per frame, matching the 60 Hz timer rate specified for CHIP-8.

## Known limitations

- `includes/cpu.h` and `src/chip8.cpp` are empty placeholder files left over from the project layout.
- There is no runtime configuration for the quirks described above (VF reset, index register behavior on register dump/load); they are fixed at compile time.
- The Makefile only builds cleanly on Windows/MinGW as written; other platforms need a manual compile command as shown above.
- CPU speed and timer rate are hardcoded constants in `main.cpp` rather than configurable options.

## Support

This is a small personal/learning project without a formal support channel. If you hit a bug or have a question, open an issue on the repository and describe what ROM you were running and what happened.

## Resources

Background reading and references used while building this emulator are listed in `resources.md`, including the CHIP-8 Wikipedia article, Cowgod's CHIP-8 technical reference, and two community write-ups on writing a CHIP-8 emulator.

## Contributing

Issues and pull requests are welcome. If you add or change opcode behavior, note which quirk convention it follows so it stays consistent with the notes above.

## License

No license file is currently included in this repository.
