// Build & run: c++ main.cpp -o app -lraylib && ./app
// Note: needs a display. Opens an 800x450 window until closed.
#include "filepicker.h"
#include "raylib.h" // raylib library

int main() {
    std::string filepath = pickModelPath();
    
    InitWindow(800, 450, "QuickRay");
    
    Camera3D camera = { 0 };
    camera.position = { 10.0f, 10.0f, 10.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    
    // Model from file
    Model model = LoadModel(filepath.c_str());
    
    // Model position
    Vector3 modelPosition = { 0.0f, 0.0f, 0.0f };

    // Model scale
    float modelScale = 1.0f;
    
    SetTargetFPS(120);

    DisableCursor();
    
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, CAMERA_FREE);

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);
            DrawGrid(20, 1.0f);
            if (filepath == "") {
                DrawCube(modelPosition, 2.0, 2.0, 2.0, GREEN);
            }
            else {
                DrawModel(model, modelPosition, modelScale, WHITE);
            } 
        EndMode3D();

        if (IsKeyPressed(KEY_O)) {
            filepath = pickModelPath();
            model = LoadModel(filepath.c_str());
        }

        DrawText("QuickRay", 20, 20, 24, GREEN);
        DrawText(filepath.c_str(), 20, 50, 18, LIGHTGRAY);
        DrawText("Press O to open file", 20, 80, 18, LIGHTGRAY);
        DrawFPS(20, 110);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
