# KU Sem 2 Project: CHIP-8 Emulator
This repository contains our second-semester Computer Science project at Kathmandu University.

We are currently building a CHIP-8 emulator from scratch using object-oriented C++. The main goal of this project is to understand how low-level computer systems work internally, especially concepts like memory handling, instruction execution, registers, and the fetch-decode-execute cycle.

This branch is mainly being used for testing, experimenting, and uploading progress as we continue developing the emulator step by step.

*Note: The project is still incomplete and many parts are still experimental. We are updating the repository as we continue learning and implementing new features.*

---

## Current Status & Roadmap

We are using this section as a progress checklist for the team.

* [x] Research CHIP-8 architecture and instruction format
* [x] Set up the initial project structure
* [x] Configure MSYS2 and MinGW64 environment
* [x] Learn basic opcode fetching and masking
* [ ] Implement the CPU fetch-decode-execute cycle
* [ ] Set up memory arrays and registers
* [ ] Build opcode execution handling
* [ ] Implement graphical display logic
* [ ] Add keyboard input mapping
* [ ] Add ROM loading support
* [ ] Run a complete CHIP-8 game ROM

---

## What We Learned So Far

### 1. Opcode Fetching

One of the first things we learned was how CHIP-8 instructions are stored in memory.

Since memory is byte-addressable but CHIP-8 instructions are 16-bit, we combine two consecutive memory locations into one opcode:

```cpp id="t7zj8h"
uint16_t opcode = (memory[pc] << 8) | memory[pc + 1];
```
(opcode formation in CHIP-8) [Diagram](https://excalidraw.com/#json=4ZnqfyRMuRu5xOrAwu-56,S3TCzXFhpU_5K3hXxcuWtA)

At first, bitwise operations looked confusing, especially shifting and masking, but after experimenting with them in code, the logic became easier to understand.

---

### 2. Bitmasking

We also learned how masking is used to isolate different parts of an opcode.

For example:

```cpp id="z1o9nr"
opcode & 0xF000
```

This helps identify the instruction category so it can later be handled inside a switch-case structure.

We are still learning how some opcode patterns work internally, but implementing them ourselves has helped us understand the concepts much better.

---

### 3. Emulator Structure

We are trying to keep different parts of the emulator separated into modules so debugging becomes easier and team members can work independently without affecting each other’s code too much.

Current project structure:

```text id="e8s4xv"
CHIP8_Emulator/
├── Makefile
├── includes/
│   ├── chip8.h
│   ├── display.h
│   └── memory.h
└── src/
    ├── main.cpp
    ├── cpu.cpp
    ├── display.cpp
    └── memory.cpp
```

---

## Development Environment

We are using MSYS2 and MinGW64 on Windows for compiling the project.

### Install g++

```bash id="f6n5wi"
pacman -S mingw-w64-x86_64-gcc
```

### Install make

```bash id="a9y4bx"
pacman -S make
```

### Add MinGW64 to PATH

Add this directory to the Windows PATH environment variables:

```text id="i4b0sv"
C:\msys64\mingw64\bin
```

This allows us to use commands like:

```bash id="e2j9qc"
g++
make
```

directly from VS Code terminal or Command Prompt.

---

## Notes

This repository is mainly being used to track our development progress and document what we are learning during the project.

A lot of emulator-related concepts were unfamiliar to us initially, so this project has become both a coding project and a learning experience at the same time.
