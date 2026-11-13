// Build & run: c++ main.cpp -o app -lraylib && ./app
// Note: needs a display. Opens an 800x450 window until closed.
#include <stdio.h>
#include <stdlib.h> // for console

#include "raylib.h" // raylib library

int main() {
    InitWindow(800, 450, "QuickRay");
    
    Camera3D camera = { 0 };
    camera.position = { 10.0f, 10.0f, 10.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    
    SetTargetFPS(60);
    
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_ORBITAL);

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);
            DrawGrid(20, 1.0f);
        EndMode3D();

        DrawText("QuickRay", 20, 20, 24, GREEN);
        DrawText("Untitled", 20, 50, 18, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
