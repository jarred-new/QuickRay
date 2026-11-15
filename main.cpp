#include "filepicker.h"
#include "arguments.h"
#include "raylib.h" // raylib library

#include <cstdlib>
#include <string>

int main(int argc, char* argv[]) {
    AppOptions options;
    const ArgumentParseResult argumentResult = parseArguments(argc, argv, options);
    if (argumentResult == ArgumentParseResult::Error) {
        return EXIT_FAILURE;
    }
    if (argumentResult == ArgumentParseResult::Help) {
        return EXIT_SUCCESS;
    }

    float modelScale = options.modelScale;
    Color modelTint = options.modelTint;
    int selectedColor = options.selectedColor;
    int selectedCamera = options.selectedCamera;

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

    SetTargetFPS(120);

    DisableCursor();
    
    while (!WindowShouldClose()) {
        UpdateCamera(&camera, static_cast<CameraMode>(selectedCamera));

        BeginDrawing();
        ClearBackground(BLACK);

        BeginMode3D(camera);
            DrawGrid(20, 1.0f);
            if (filepath == "" || filepath == "cube") {
                DrawCube(modelPosition, 2.0f * modelScale, 2.0f * modelScale,
                         2.0f * modelScale, modelTint);
            }
            else if (filepath == "sphere") {
                DrawSphere(modelPosition, modelScale, modelTint); // Draw sphere if no model is loaded
            }
            else if (model.meshCount == 0) { // model count error on null or empty
                DrawText("Error: Model has no meshes to draw.", 10, 10, 20, RED);
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
