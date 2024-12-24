#include "include/raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"
#include "include/raymath.h"
#include <iostream>

//SETUP STRUCTS / CLASSES / FUNCTIONS / MISC. VARIABLES HERE


int main() {
  const int screenWidth = 1280;
  const int screenHeight = 720;
  InitWindow(screenWidth, screenHeight, "name here");
  SetTargetFPS(146);

  //SETUP STATIC STATE EFFECTS
  
  while (!WindowShouldClose()) {
    //INITIALIZE VARIABLES HERE


    //INITIALIZE MAIN STATE MACHINE HERE
    BeginDrawing();
      ClearBackground(GRAY);
    EndDrawing();
  }

  CloseWindow();
  
  return 0;
}
