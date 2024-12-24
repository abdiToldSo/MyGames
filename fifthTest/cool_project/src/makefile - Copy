CXX = g++
CXXFLAGS = -O1 -Wall -Wno-missing-braces -I include/ -L lib/ -lraylib -lwinmm -lgdi32
#IODIR = ../../main_IO/

game: main.cpp include/raylib.h
	$(CXX) main.cpp -o game.exe $(CXXFLAGS)

run:
	./game.exe

build:
	$(CXX) main.cpp -o game.exe $(CXXFLAGS)
	./game.exe
#game.exe sounds so sketch, use game name instead for future projects

#make:
#	g++ main.cpp -o game.exe -O1 -Wall -Wno-missing-braces -I include/ -L lib/ -lraylib -lwinmm -lgdi32
