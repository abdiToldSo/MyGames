#include "include/raylib.h"
#include "include/raymath.h"
#include "include/rlgl.h"
#include <iostream>

int main(void)
{
  const int screenWidth = 800;
  const int screenHeight = 600;
  SetConfigFlags(FLAG_MSAA_4X_HINT);
  InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
  //Vector3 cubePosition = {0.0f, 1.0f, 0.0f};
  //Vector3 cubeSize = {2.0f, 2.0f, 2.0f};
  SetTargetFPS(146);
  SetWindowState(FLAG_WINDOW_RESIZABLE);
  //camera.zoom = 1.0f;

  Camera3D camera = { 0 };
  camera.position = (Vector3){0.0f,10.0f,10.0f};
  camera.target = (Vector3){ 0.0f,0.0f,0.0f};
  camera.up = (Vector3){0.0f,1.0f,0.0f};
  camera.fovy = 45.0f;
  camera.projection = CAMERA_PERSPECTIVE;
  //camera.position

  int cameraMode = CAMERA_FREE;

  Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
  Vector3 cubePosition2 = { 2.0f, 0.0f, 0.0f };
  Vector2 cubeScreenPosition = {0.0f, 0.0f}; //Camera2D camera = {0};
  Vector2 cubeScreenPosition2 = {2.0f, 0.0f}; //Camera2D camera = {0}; 

  Texture2D bill = LoadTexture("billy.png");
  Vector3 billPosition = {1.0f, 2.0f, 0.0f};
  Vector3 mapPosition = {-16.0f, 0.0f, -8.0f};
  DisableCursor();


  Image image = LoadImage("cubicmap.png");
  Image amen = LoadImage("billy.png");
  Image cube = LoadImage("cubicmap.png");
  Texture2D cubicmap = LoadTextureFromImage(cube);
  Mesh mesh = GenMeshCubicmap(cube, (Vector3){1.0f, 1.0f, 1.0f});
  Model model = LoadModelFromMesh(mesh);
  model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = bill;
  

  //bool exitWindowRequested = false;
  //bool exitWindow = false;

  // Detect if X-button or KEY_ESCAPE have been pressed to close window
  //if (WindowShouldClose() || IsKeyPressed(KEY_ESCAPE)) exitWindowRequested = true;

  //while (!exitWindow)
  while (!WindowShouldClose())
  {
    /*
    if (IsKeyDown(KEY_W)) {
      camera.position -= (Vector3){0.0f,0.0f,0.5f};
    }
    if (IsKeyDown(KEY_S)) {
      camera.position += (Vector3){0.0f,0.0f,0.5f};
    }
    */

    UpdateCamera(&camera, cameraMode);
    cubeScreenPosition = GetWorldToScreen( (Vector3) {cubePosition.x, cubePosition.y + 2.5f, cubePosition.z}, camera);
    cubeScreenPosition2 = GetWorldToScreen( (Vector3) {cubePosition2.x, cubePosition2.y + 2.5f, cubePosition2.z}, camera);
    billPosition = Vector3Lerp(billPosition, cubePosition2, 0.0005f); 
    BeginDrawing();
      ClearBackground(RAYWHITE);
      //BeginDrawing2D(camera);
      //
      //BeginDrawing3D();

      BeginMode3D(camera);

        DrawModel(model, mapPosition, 1.0f, WHITE);
        DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
        DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, BLUE);


        DrawBillboard(camera, bill, billPosition, 2.0f, WHITE);

        DrawCircle3D((Vector3) {0.0, 2.0f, 0.0f}, 2.0f, (Vector3) {1, 0, 0}, 90.0f , RED);        
        DrawSphere((Vector3) {0.0f, 2.0f, 0.0f}, 1.0f, RED);
    
        DrawCube(cubePosition2, 2.0f, 2.0f, 2.0f, BLUE);
        DrawCubeWires(cubePosition2, 2.0f, 2.0f, 2.0f, GREEN);
        DrawGrid(10, 1.0f);

      EndMode3D();

      //if (exitWindowRequested) {
        //DrawRectangle(0,100, screenWidth, 200, BLACK);
      //  DrawText("where do you think ur going bitch as nigga fuck up outta here dumbass worrrrrrr", 40, 180, 30, BLACK);
      //}

     /*std::cout << "X-Axis: " << camera.position.x << std::endl;
     std::cout << "Y-Axis: " << camera.position.y << std::endl;
     std::cout << "Z-Axis: " << camera.position.z << std::endl;*/
     DrawText("wassguuuud",0,0,26,BLACK);
     DrawFPS(0,20);
     //DrawText("red fucking stupid box lmao", (int)cubePosition.x - MeasureText("red fucking stupid box lmao", 20)/2, (int)cubePosition.y, 20, BLACK );
     DrawText("red fucking stupid box lmao", (int)cubeScreenPosition.x - MeasureText("red fucking stupid box lmao",20)/2, (int)cubeScreenPosition.y, 20, BLACK );
     DrawText("another stupid fucking box lol", (int)cubeScreenPosition2.x - MeasureText("another stupid fucking box lol", 20)/2, (int)cubeScreenPosition2.y, 20, PURPLE);
      //rlPushMatrix();
      //  rlTranslatef(0, 25*50,0);
      //  rlRotatef(90,1,0,0);
      //  DrawGrid(100,50);
      //rlPopMatrix();
      DrawTextureEx(cubicmap, (Vector2){screenWidth - cubicmap.width*4.0f - 20, 20.0f}, 0.0f, 4.0f, WHITE);
      DrawRectangleLines(screenWidth - cubicmap.width*4 - 20, 20, cubicmap.width*4, cubicmap.height*4, GRAY);



      //DrawCubeV(cubePosition, cubeSize, BLACK);
      //DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
      

      /*if (!IsWindowFocused()) {
        DrawText("BITCH ASS NIGGA LETS GOOOOOOOOOOOOOOOOOOOOOOO", 190,250,30, LIGHTGRAY);
      } else {
        DrawText("", 190,250,30, LIGHTGRAY);
      }*/
    EndDrawing();
  }

  UnloadTexture(cubicmap);
  //UnloadTexture(texture);
  UnloadModel(model);

  CloseWindow();

  return 0;

}
