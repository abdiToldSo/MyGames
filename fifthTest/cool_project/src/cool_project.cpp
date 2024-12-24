/*******************************************************************************************
*
*   project_name
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2024 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "include/raylib.h"

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif

//----------------------------------------------------------------------------------
// Local Variables Definition (local to this module)
//----------------------------------------------------------------------------------
Camera camera = { 0 };
Vector3 cubePosition = { 0 };

//----------------------------------------------------------------------------------
// Local Functions Declaration
//----------------------------------------------------------------------------------
// static void UpdateDrawFrame(void);          // Update and draw one frame
static void UpdateDrawFrame(Model model, Texture2D texture);          // Update and draw one frame

//----------------------------------------------------------------------------------
// Main entry point
//----------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib - project_name");

    camera.position = (Vector3){ 3.0f, 3.0f, 2.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Model model = LoadModel("castle.obj");
    Texture2D texture = LoadTexture("castle_diffuse.png");
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

    BoundingBox bounds = GetMeshBoundingBox(model.meshes[0]);

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(144);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateDrawFrame(model, texture);
    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture);
    UnloadModel(model);
    
    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Update and draw game frame
// static void UpdateDrawFrame(void)
static void UpdateDrawFrame(Model model, Texture2D texture)          // Update and draw one frame
{
    // Update
    //----------------------------------------------------------------------------------
    // UpdateCamera(&camera, CAMERA_ORBITAL);
    UpdateCamera(&camera, CAMERA_FIRST_PERSON);
    DisableCursor();
    model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
    //----------------------------------------------------------------------------------

    // Draw
    //----------------------------------------------------------------------------------
    BeginDrawing();

        ClearBackground(RAYWHITE);

        BeginMode3D(camera);

            DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
            DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
            DrawGrid(10, 1.0f);

            DrawModel(model, cubePosition, 1.0f, WHITE);

        EndMode3D();

        DrawText("Welcome to raylib basic sample", 10, 40, 20, DARKGRAY);

        DrawFPS(10, 10);

    EndDrawing();
    //----------------------------------------------------------------------------------
}

//nice attempt, but doin 3d in raylib too much
//stick to godot rn
