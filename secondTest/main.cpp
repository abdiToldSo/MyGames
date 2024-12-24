//Finished 7/4/24
//Time: Like a day and a half 
/*Notes:

  Purple circle math too complicated owie
  now i gotta comment this shit too DX<
  gl future me, your gonna need it big time
  also blue lock episode nagi was shit ngl
  300 lines of junk lol, this shit was fun tho
  additoinally helix editor is so cool i can do some sick shit with it imma experiment :D
  tip to future, press space/leader in nor mode to do some cool shit (perform code action, open jumplist picker, open diagnostic picker, etc literally so much)
  i love u <3
  im just tryna get geeked all night, im with twin, pur the ritz in the sprite
  hold my hand if you think its for life
  cant believe they aint gave you
  wait wait wha everybody know im goated yuh
  caught the five but she know how the fuck to throw it up
  i caught a drank at nobu now im thrown as fuck huh wha
  what you mean you wanted -
  i lovvvvvvvvvuuuu 
  Research:
    Intersection of two circles (Paul Bourke, paulbourke.net)
    Intersecting area of two circles with implementation in C++ (Jan Sellner, milania's blog)1
  
*/
#include <iostream>
#include "include/raylib.h"
#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"
#include "include/raymath.h"
#include <cmath>

//GAME STATES
typedef enum GameScreen {HOME = 0, GAME, WIN} GameScreen;

//WINDOW PROPS
const int width = 1280;
const int height = 720;
int fps = 144;

//Image favicon = LoadImage("test.jpg");
//SetWindowIcon(favicon);
//^^^should change window icon but doesn't for some reason

//DEFINE CIRCLE STRUCT
struct Circle {
  Vector2 pos = {640, 360};
  float radius = 20.0f;
  Vector2 dir = {1,1};
  Color color = RED;
  float speed = 1.0f;
};

//DRAW CIRCLE FUNCTION
void CircleDraw(Circle &C) {
  DrawCircle(C.pos.x, C.pos.y, C.radius, C.color);
}

//MOVE CIRCLE FUNCTION
void CircleMove(Circle &C) {
  
  if (C.pos.x + C.radius > width) {
    C.dir.x = -1;
  } else if (C.pos.x - C.radius < 0) {
    C.dir.x = 1;
  }
   if (C.pos.y + C.radius > height) {
    C.dir.y = -1;
  } else if (C.pos.y - C.radius < 0) {
    C.dir.y = 1;
  }
  C.pos.x += 1.0f * C.dir.x * C.speed;
  C.pos.y += 1.0f * C.dir.y * C.speed;
}

//CIRCLE COLLISION DETECTOR
bool CirclesCollided(Circle &C, Circle &K) {
  return CheckCollisionCircles(C.pos, C.radius, K.pos, K.radius);
}

//INITIALIZE CIRCLE POSITIONS
void InitPositions(Circle &C, Circle &K, bool &initQ) {
  srand(time(NULL));
  if (initQ) {
    return;
  } else {
  C.pos.x = std::rand() % GetScreenWidth();
  C.pos.x += (C.pos.x + C.radius > GetScreenWidth()) ? -C.radius : 0;
  C.pos.x += (C.pos.x - C.radius < 0) ? C.radius : 0;

  C.pos.y = std::rand() % GetScreenHeight();
  C.pos.y += (C.pos.y + C.radius > GetScreenHeight()) ? -C.radius : 0;
  C.pos.y += (C.pos.y + C.radius < 0) ? C.radius : 0;
    
  K.pos.x = std::rand() % GetScreenWidth();
  K.pos.x += (K.pos.x + K.radius > GetScreenWidth()) ? -K.radius : 0;
  K.pos.x += (K.pos.x - K.radius < 0) ? K.radius : 0;

  K.pos.y = std::rand() % GetScreenHeight();
  K.pos.y += (K.pos.y + K.radius > GetScreenHeight()) ? -K.radius : 0;
  K.pos.y += (K.pos.y + K.radius < 0) ? K.radius : 0;

  
  initQ = true;
  }
}

//float cursorX, cursorY;
//Vector2 cursorPos = (Vector2) {cursorX, cursorY};

//CHECK IF CURSOR IS WITHIN BOTH CIRCLES
bool CheckCursor(Circle &C, Circle &K) {
  float cursorX = GetMouseX(), cursorY = GetMouseY();
  Vector2 cursorPos = (Vector2) {cursorX, cursorY};
  //if cursor is within both circles, return true to add points
  if (CheckCollisionPointCircle(cursorPos, C.pos, C.radius) && CheckCollisionPointCircle(cursorPos, K.pos, K.radius)) {
    return true;
  } else { return false;}
}

int main() {
  //INIT CIRCLES
  Circle ben, ken;
  ken.pos = {660.5, 420.5};
  ken.color = BLUE;

  //COLLISIONS
  Color collisionColor = RED;
  const char* collision;
  Vector2 collisionCenterPoint;
  //SCORE
  int score = 0;
  std::string scoreText;
  int targetScore = 100;
  
  //ETC
  GameScreen currentScreen = HOME;
  int difficulty = 0;
  bool initialized = false;
  float distance;
  float a,h;
  bool exit = false;
  
  //INIT WINDOW
  InitWindow(width, height, "test2");
  SetTargetFPS(fps);
  
  while (!WindowShouldClose()) {
    //GAME LOGIC
    switch(currentScreen) {
      case HOME:
      {
        //std::cout << currentScreen << std::endl;
        //press space to start game
        if (IsKeyPressed(KEY_SPACE)) {
          currentScreen = GAME;
        }
      } break;

      case GAME:
      {
        std::cout << currentScreen << std::endl;
        //if score reaches target, proced to win screen
        if (score >= targetScore) {
          currentScreen = WIN;
        }
      } break;

      case WIN:
      {
        std::cout << currentScreen << std::endl;
        //implement gui if needed
      } break;
    }
    
    //INIT DIFFICULTY
    switch(difficulty) {
      case 0: //EASY
      {
      ben.radius = 100.0f;
      ken.radius = 100.0f;
      //if (!initialized) {InitPositions(ben, ken); initialized = true;}
      //^^^ dont use, will crash program on start
      InitPositions(ben, ken, initialized);
      }
      break;
    
      case 1: //MEDIUM
      {
      ben.radius = 80.0f;
      ken.radius = 80.0f;
      ben.speed = 1.5f;
      ken.speed = 1.5f;
      
      InitPositions(ben, ken, initialized);
      //if (!initialized) {InitPositions(ben, ken); initialized = true;}
      } 
      break;
      case 2: //HARD
      {
      ben.radius = 65.0f;
      ken.radius = 65.0f;
      ben.speed = 2.0f;
      ken.speed = 2.0f;      
      InitPositions(ben, ken, initialized);
      //if (!initialized) {InitPositions(ben, ken); initialized = true;}
      }
      break;
    } 
    
    BeginDrawing();
      ClearBackground(GRAY);
      
      switch (currentScreen){

        case HOME: //HOME SCREEN LOOK

          DrawText("Press Space to Start", (GetScreenWidth()/ 2 - MeasureText("Press Space to Start", 40)/2), (GetScreenHeight()/2 - 20), 40, BLACK);
          GuiToggleGroup((Rectangle) { float(GetScreenWidth()/2.0f - 150), float(GetScreenHeight()/2.0f + 45), 100, 50}, "EASY;MEDIUM;HARD", &difficulty );
          break;
        case GAME: //GAME VISUALS

          //draw my beautiful, veluptuous, curvy balls
          CircleDraw(ben);
          CircleDraw(ken);

          //draw current fps in top-left corner
          DrawFPS(0,0);
      
          //GLOBAL STATS
          DrawText(TextFormat("X:%0.0f",ben.pos.x), 0, 20, 20, RED);
          DrawText(TextFormat("Y:%0.0f",ben.pos.y), 0, 40, 20, RED);
          DrawText(TextFormat("X:%0.0f",ken.pos.x), 0, 60, 20, BLUE);
          DrawText(TextFormat("Y:%0.0f",ken.pos.y), 0, 80, 20, BLUE);
          DrawText(collision, 0, 100, 20, collisionColor);
          DrawText(TextFormat("SCORE:%i", score), 0, 120, 20, BLACK);
          DrawText(TextFormat("A:%0.2f", a), 0, 140, 20, BLACK);
          DrawText(TextFormat("H:%0.2f", h), 0, 160, 20, BLACK);
          DrawText(TextFormat("HX:%0.2f", collisionCenterPoint.x), 0, 180, 20, BLACK);
          DrawText(TextFormat("HY:%0.2f", collisionCenterPoint.y), 0, 200, 20, BLACK);
          //GLOBAL STATS

          //Move my beautiful, veluptuous, curvy balls
          CircleMove(ben);
          CircleMove(ken);
      
          //check if my beautiful, veluptuous, curvy balls was collided with each other dont want to deal with that shit hurts
          collision = CirclesCollided(ben, ken) ? "True" : "False";
          collisionColor = CirclesCollided(ben, ken) ? GREEN : RED;

          //IF BALLS COLLIDE
          if ( CirclesCollided(ben, ken) ) {

            //calculate distance between position of two beautiful, veluptuous, curvy balls my beloved mwah
            distance = Vector2Distance(ben.pos, ken.pos);
            //distance between first circle (ben) and intersection center point
            a = ( ((ben.radius * ben.radius) - (ken.radius * ken.radius) + (distance * distance))/ (2.0 * distance));
            //height/vertical radius of intersection
            h = std::sqrt( ( (ken.radius * ken.radius) - (a*a) ) );
            //calculate center point of collision mes thinks kinda janky tho
            collisionCenterPoint = Vector2Add(ben.pos, ( Vector2Scale(Vector2Scale(Vector2Subtract(ken.pos, ben.pos), a), 1/distance ) ));
            //draw line between first beautiful circle ben & collision center point
            DrawLineV(ben.pos, collisionCenterPoint, BLACK);
            //draw point of intersection mes thinks super fucking jank tbh
            DrawCircleV(collisionCenterPoint, 10.0f, PURPLE);

            //potential choices if they work
            //DrawCircleSector(collisionCenterPoint, ben.radius, 90.0f, 270.0f, 0, PURPLE);
            //collisionCenterPoint = ben.pos + (a)(ken.pos - ben.pos) / distance;
            //potential choices if they work

            //draw purple circle (intersection area mes thinks super fucking jank tho)
            DrawEllipse(collisionCenterPoint.x, collisionCenterPoint.y, (distance - a), h, PURPLE);
          }
     
          //ADD POINTS
          if ( CheckCursor(ben, ken) ) score += 1;

          //BACK BUTTON (to go back to home screen)
          if (GuiButton( (Rectangle) {GetScreenWidth()/2.0f + GetScreenWidth()/2.5f, 10, 100.0f, 60.0f}, "BACK")) {
            //reset props!
            score = 0;
            initialized = false;
            InitPositions(ben, ken, initialized);
            currentScreen = HOME;
            //reset props!
          }
          
          break;
        case WIN: //WIN SCREEN LOOK
      
          DrawText("YOU WINNN!!!", (GetScreenWidth()/ 2 - MeasureText("You WINNN!!!", 40)/2), (GetScreenHeight()/2 + 50), 40, BLACK);

          //RESTART BUTTON
          if(GuiButton((Rectangle) {(GetScreenWidth()/2.0f - 50.0f),(GetScreenHeight()/2.0f - 30.0f),100.0f,60.0f}, "RESTART")) {
            //reset props!
            score = 0;
            initialized = false;
            InitPositions(ben, ken, initialized);
            currentScreen = HOME;
            //reset props!
          }
      
          //EXIT BUTTON
          if(GuiButton((Rectangle) {(GetScreenWidth()/2.0f - 50.0f),(GetScreenHeight()/2.0f - 90.0f),100.0f,60.0f}, "EXIT")) {
            exit = true;          
          }
          break;
      }
            
    EndDrawing();
    //if your broke, dirty ass wants to quit do so, break the cycle shit i mean loop
    if (exit) { break; } 
  }
  return 0;
}
//ideaa: make balls attracted to center gravity, could replace balls with planets & center the sun
//ideaa: post normal project to github, have a folder of directors cuts to just be me lol cause this shit cannot be good
