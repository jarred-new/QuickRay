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

    // Model Color tint and selection
    Color modelTint = WHITE;
    int selectedColor = 0;

    // Camera Selection
    int selectedCamera = 0; // 0: Free, 1: Orbit, 2: First Person, 3: Third Person
    
    SetTargetFPS(120);

    DisableCursor();
    
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, static_cast<CameraMode>(selectedCamera));

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);
            DrawGrid(20, 1.0f);
            if (filepath == "") {
                DrawCube(modelPosition, 2.0, 2.0, 2.0, GREEN);
            }
            else {
                DrawModel(model, modelPosition, modelScale, modelTint);
            } 
        EndMode3D();

        if (IsKeyPressed(KEY_O)) {
            filepath = pickModelPath();
            model = LoadModel(filepath.c_str());
        }

        if (IsKeyPressed(KEY_C)) {  
            selectedColor = (selectedColor + 1) % 4; // Cycle through 4 colors
            switch (selectedColor) {
                case 0: modelTint = WHITE; break;
                case 1: modelTint = RED; break;
                case 2: modelTint = GREEN; break;
                case 3: modelTint = BLUE; break;
            }
        }
        
        if (IsKeyPressed(KEY_EQUAL)) { // '+' key to increase scale
            modelScale += 0.1f;
        }
        if (IsKeyPressed(KEY_MINUS)) { // '-' key to decrease scale
            modelScale -= 0.1f;
        }

        if (IsKeyPressed(KEY_ONE)) { selectedCamera = CAMERA_FREE; } // Free camera
        if (IsKeyPressed(KEY_TWO)) { selectedCamera = CAMERA_ORBITAL; } // Orbit camera
        if (IsKeyPressed(KEY_THREE)) { selectedCamera = CAMERA_FIRST_PERSON; } // First Person camera
        if (IsKeyPressed(KEY_FOUR)) { selectedCamera = CAMERA_THIRD_PERSON; } // Third Person camera

        DrawText("QuickRay", 20, 20, 24, GREEN);
        DrawText(filepath.c_str(), 20, 50, 18, LIGHTGRAY);
        DrawText("Press O to open file, C to change color,", 20, 80, 12, LIGHTGRAY);
        DrawText("+ or - to scale model", 20, 100, 12, LIGHTGRAY);
        DrawText("Press 1-4 to change camera mode", 20, 120, 12, LIGHTGRAY);
        DrawFPS(20, 135);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
