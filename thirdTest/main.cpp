#include "include/raylib.h"
#include <iterator>
#define RAYGUI_IMPLEMENTATION
#include "include/raygui.h"
#include "include/raymath.h"
#include <iostream>
#include <vector>
int screenWidth = 1280;
int screenHeight = 720;
Font fonts[1] = {};
  
  
enum testState { HOME=0, REACTIONTITLE, REACTIONTIME, REACTIONRESULT, AIMTITLE, AIM, AIMRESULT };
int currentState = HOME;
int posX, posY;

Color readyRT = GREEN;
Color waitRT = RED;
Color titleRT = PURPLE;
bool clickedWhenReady = false;
bool clickedEarly = false;
int randFrames = GetRandomValue(3, 9);
//int randFrames = GetRandomValue(1, 2);
//int randFrames = 12;
float currTime = 0;
int randomTime;

bool aimCheck = 1;
void InitTime(int *time) {
  time = 0;
}

typedef struct {float lifeTime; } Timer;

void StartTimer(Timer *timer, float lifeTime) {
  if ( timer != NULL ) timer->lifeTime = lifeTime;
}

void UpdateTimer(Timer *timer) {
  if (timer != NULL && timer->lifeTime > 0) timer->lifeTime -= GetFrameTime(); 
}

bool TimerDone(Timer* timer) {
  if (timer != NULL) return (timer->lifeTime <= 0);
}

Timer reactionTimer;

/*void DrawReactionButton() {
  if (!TimerDone(&reactionTimer))
}*/

void TargetDraw(int time) {
    clickedWhenReady = false;
    clickedWhenReady = false;
    currTime = 0;
    while ( ( currTime < time ) ) {
      ClearBackground(RED);
      currTime+= 0.001f;
    }
    //ClearBackground(GREEN);
  }
/*

typedef struct Circle {float radius; Vector2 pos; 
  Circle() {
    radius = 65.0f; pos = (Vector2) { ( rand() % GetScreenWidth() / 6.0f) , ( rand() % GetScreenHeight() / 6.0f)};  
  }
   
} Circle;

int CircleCount = 10;
std::vector<Circle> cTargets(10);
void InitAim() {
//  while (CircleCount) {
    Circle temp = Circle();
    cTargets.push_back(temp);
    CircleCount-= 1;
  }
//}
*/
int main () {
  InitAudioDevice();
  Sound hooray = LoadSound("hoorayyy.wav");
  Sound incorrect = LoadSound("incorrect.mp3");
  Sound bgMusic = LoadSound("music1.wav");
  SetSoundVolume(bgMusic, 0.1f);
  Timer reactionTimer = { 0 };
  float ballLife = 2.0f;
  InitWindow(screenWidth, screenHeight, "thirdTest");
  Image thumbsupI = LoadImage("thumbsup.png");
  Image thumbsdownI = LoadImage("thumbsdown.png");
  Texture thumbsup = LoadTextureFromImage(thumbsupI);
  Texture thumbsdown = LoadTextureFromImage(thumbsdownI);
  //Texture thumbsup = LoadTexture("thumbsup.png");
  UnloadImage(thumbsupI);
  UnloadImage(thumbsdownI);
  SetTargetFPS(146);
  fonts[0] = LoadFont("Comic Sans MS.ttf");
  Vector2 titlePos {( GetScreenWidth()/2.0f - MeasureText("AIM TRAINER EXTREME", 80)/2.0f), ( GetScreenHeight()/2.0f - 40 )};
  bool reactionStart = false;
  
//  Vector2 titlePos = { GetScreenWidth()/2.0f - MeasureText("AIM TRAINER EXTREME", 80) / 2.0f ) , GetScreenHeight()/2.0f - 50) };
//  Vector2 test = {(1), (2)};
  
  switch (currentState) {
    case HOME:
        PlaySound(bgMusic);
        //PlaySound(hooray);
        break;

    //case AIM:
    case REACTIONTIME:
/*      if (clickedWhenReady) {
        PlaySound(hooray);
        currentState = HOME;
      } else if (clickedEarly) {
        PlaySound(incorrect);
        currentState = HOME;
    }
  */
        if ( IsMouseButtonDown(KEY_F) ) StartTimer(&reactionTimer, 2.0f);
        UpdateTimer(&reactionTimer);
      break;  
  }
  /*
    
        while ( !IsKeyPressed(KEY_SPACE) ) {
          ClearBackground(PURPLE);
          DrawTextEx(fonts[0], "PRESS SPACE TO START", titlePos, 80, 1, BLACK);
        }
*/
  bool backgroundReady = 0;
  while (!WindowShouldClose()) {
      if ( !IsSoundPlaying(bgMusic) ) {PlaySound(bgMusic);}
      if ( IsKeyDown(KEY_SPACE) ) StartTimer(&reactionTimer, ballLife);
      UpdateTimer(&reactionTimer);
      if (TimerDone(&reactionTimer)) { backgroundReady = true; reactionStart = false; } else {backgroundReady = false;}  
    
      BeginDrawing();
    
      randomTime = randFrames*GetFPS();
      ClearBackground(GRAY);
      switch (currentState) {
      case HOME:
        //InitTime(&currTime);
        currTime -= currTime;
        DrawTextEx(fonts[0], "AIM TRAINER EXTREME", titlePos, 80, 1, BLACK);
//        if (GuiButton((Rectangle){GetScreenWidth()/2.0f+55, GetScreenHeight()/2.0f + 100, 100.0f, 100.0f }, "AIM")) /*currentState = AIM*/ PlaySound(incorrect);
        if (GuiButton((Rectangle){GetScreenWidth()/2.0f+55, GetScreenHeight()/2.0f + 100, 100.0f, 100.0f }, "AIM")) /*currentState = AIM*/ currentState = AIMTITLE;
        if (GuiButton((Rectangle){GetScreenWidth()/2.0f-55, GetScreenHeight()/2.0f + 100, 100.0f, 100.0f }, "REACTION TIME")) currentState = REACTIONTITLE;
        //DrawText("AIM TRAINER EXTREME", ( GetScreenWidth()/2 - MeasureText("AIM TRAINER EXTREME", 80) / 2 ), 
        break;

      case REACTIONTITLE:
        ClearBackground(PURPLE);
        DrawTextEx(fonts[0], "PRESS SPACE TO START", titlePos, 80, 1, BLACK);
        if ( IsKeyPressed(KEY_SPACE) ) {
          currentState = REACTIONTIME;
        }
        break;
        
      case REACTIONTIME:
        DrawFPS(0,100);
        //DrawTextEx(fonts[0], TextFormat("randTime: %i", randomTime), (Vector2){0,0}, 80,1,BLACK);
        DrawTextEx(fonts[0], TextFormat("currTime: %0.2fms", currTime), (Vector2){0,0}, 80,1,BLACK);
        //DrawTextEx(fonts[0], "PRESS SPACE TO START", titlePos, 80, 1, BLACK);
        //std::cout << currTime << std::endl;
        if (!TimerDone(&reactionTimer) && !reactionStart) { 
          DrawTextEx(fonts[0], "wait...", titlePos, 80, 1, BLACK);
          ClearBackground(RED); 
        } else { 
          ClearBackground(GREEN); 
          currTime += ( (GetFrameTime() * GetFPS()) / (GetFPS() / 1000.0f) );
          DrawTextEx(fonts[0], "PRESS V!!!", (Vector2){( GetScreenHeight()/2.0f /*- MeasureText("CLICK!!!", 80)/2.0f*/ ), ( GetScreenWidth()/2.0f - MeasureText("CLICK!!!", 80) )}, 80,1,BLACK);
        } 
        //if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        if ( IsKeyPressed(KEY_V) ) {
        //if ( IsKeyReleased(KEY_SPACE) ) {
          if ( backgroundReady ) {
            PlaySound(hooray);
            reactionStart = false;
            currentState = REACTIONRESULT;
          } else {
            PlaySound(incorrect);
            reactionStart = false;
            currentState = REACTIONRESULT;
          }
        }
        break;

      case REACTIONRESULT:
        ClearBackground(PINK);
        DrawTextEx(fonts[0], TextFormat("RESULT: %0.1fms", currTime), titlePos, 80, 1, BLACK);
        DrawTextEx(fonts[0], "PRESS SPACE TO GO BACK", Vector2SubtractValue(titlePos, 105), 80, 1, BLACK);
        if (currTime <= 0.0f) {
          DrawTexture(thumbsdown, titlePos.x + GetScreenWidth()/2.0f, titlePos.y, WHITE);
        } else {
         DrawTexture(thumbsup, titlePos.x + GetScreenWidth()/2.0f, titlePos.y, WHITE);
        }
        //DrawTexture(thumbsup, titlePos.x + GetScreenWidth()/2.0f, titlePos.y, WHITE);
        if ( IsKeyPressed(KEY_SPACE) ) currentState = HOME;        
        break;
        
      case AIMTITLE:
        ClearBackground(PURPLE);
        DrawTextEx(fonts[0], "PRESS SPACE TO START", titlePos, 80, 1, BLACK);
        if ( IsKeyPressed(KEY_SPACE) ) {
          currentState = AIM;
        }
        break;

      case AIM:/*
        if (aimCheck) {
          InitAim();
          aimCheck = false;
        }
        
        for (int i = 0; i < cTargets.size(); i++) {
          DrawCircle(cTargets[0].pos.x, cTargets[0].pos.y, cTargets[0].radius, RED);
        }*/
//        std::cout << cTargets[0].radius << std::endl;
        break;

      case AIMRESULT:
        break;
    }
      
    EndDrawing();
  }    

  UnloadFont(fonts[0]);
  UnloadSound(incorrect);
  UnloadSound(hooray);
  UnloadTexture(thumbsup);
  CloseWindow();
  return 0;
}

//note:: check tutorial on raylib timers, looks complex but my solution is not right so far doing it blind tbh
/*

  steps:
1. initialize random num then multiply it by current frame rate
2. call function to update screen green when currtime variable is greater than random time lol
3. click to return home with either a horraaay >XD or *LOUD INCORRECT BUZZER*

think current issue is that fact that we are creating a while loop every time we render a frame which is prob 
why the screen is always red lol
we got this just need a tutorial or two
im just nah

7/5/24
got timers fixed, a lot simpler than what i was doing
we damn near finished with reaction time just some quality of life updates yipeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee!!!!!!!!!

*/
