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
  
  Texture2D knight = LoadTexture("mainSprites/_Attack.png");
  Rectangle frameRec = { 0.0f, 0.0f, (float)knight.width/4, (float)knight.height };
  
  int currFrame = 0;
  int framesCounter = 0;
  int frameSpeed = 8;
  
  
  //SETUP STATIC STATE EFFECTS
  
  while (!WindowShouldClose()) {
    //INITIALIZE VARIABLES HERE


    //INITIALIZE MAIN STATE MACHINE HERE
    BeginDrawing();
      ClearBackground(GRAY);
      DrawTexture(knight, 15, 40, WHITE);
      //DrawTextureRec(knight, frameRec, (Vector2) { screenWidth/2.0f, screenHeight/2.0f}, WHITE);
      DrawTexturePro(knight, frameRec, frameRec, (Vector2) { screenWidth/2.0f, screenHeight/2.0f}, 0.0f, WHITE);
    
    EndDrawing();
  }

  UnloadTexture(knight);
  CloseWindow();
  
  return 0;
}
 
