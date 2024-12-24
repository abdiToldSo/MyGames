CXX = g++
CXXFLAGS = -O1 -Wall -Wno-missing-braces -I include/ -L lib/ -lraylib -lwinmm -lgdi32
#IODIR = ../../main_IO/
CFLAGS = -DVAR='#include "include/raylib.h"'
define TEST
	this is a test lol
endef
game: main.cpp include/raylib.h
	$(CXX) main.cpp -o game.exe $(CXXFLAGS)

run:
	./game.exe

build:
	$(CXX) main.cpp -o game.exe $(CXXFLAGS)
	./game.exe

all:
	@echo "$$CFLAGS" > test.cpp
#	$test=@'
#		Test
#		Test
#	'@
#	/*cat > $FILE <<- EOF
#		#include "raylib.h"
#		int main() {
#			const int screenWidth = 1280;
#			const int screenHeight = 720;
#
#			InitWindow(screenWidth, screenHeight, "fourthTest");
#			SetTargetFPS(146);
#		}
#		
#		EOF
#
#game.exe sounds so sketch, use game name instead for future projects

#make:
#	g++ main.cpp -o game.exe -O1 -Wall -Wno-missing-braces -I include/ -L lib/ -lraylib -lwinmm -lgdi32
