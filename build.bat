@echo off
echo Building CHIP-8 Emulator project structure...

REM Create directories
mkdir includes
mkdir src
mkdir bin
mkdir build
mkdir roms

REM Create header files in the includes/ directory
type nul > includes\chip8.h
type nul > includes\memory.h
type nul > includes\cpu.h
type nul > includes\display.h

REM Create source files in the src/ directory
type nul > src\chip8.cpp
type nul > src\memory.cpp
type nul > src\cpu.cpp
type nul > src\display.cpp
type nul > src\main.cpp

REM Create root project files
type nul > CMakeLists.txt
type nul > .gitignore
type nul > README.md

echo Project structure created successfully!
pause
