CXX = g++
CXXFLAGS = -fdiagnostics-color=always -g -Iincludes
LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -mwindows

SRC = $(wildcard src/*.cpp)
OUT = build/game.exe

all: builddir
	$(CXX) $(CXXFLAGS) $(SRC) -o $(OUT) $(LDFLAGS)

builddir:
	if not exist build mkdir build

run: all
	./$(OUT)

clean:
	if exist build\game.exe del /Q build\game.exe
