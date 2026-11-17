#include "filepicker.h"
#include "arguments.h"
#include "raylib.h"

#include <cstdlib>
#include <iostream>
#include <string>

namespace {
bool TryLoadModel(const std::string& path, Model& model) {
    model = { 0 };

    if (path.empty() || path == "cube" || path == "sphere") {
        return true;
    }

    if (!isValidModelInput(path)) {
        std::cerr << "Error: Invalid model path: " << path << '\n';
        return false;
    }

    model = LoadModel(path.c_str());
    return model.meshCount > 0;
}
}

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

    std::string filepath = options.modelFilePath.empty() ? pickModelPath() : options.modelFilePath;

    InitWindow(800, 450, "QuickRay");
    SetTargetFPS(120);

    Camera3D camera = { 0 };
    camera.position = { 10.0f, 10.0f, 10.0f };
    camera.target = { 0.0f, 0.0f, 0.0f };
    camera.up = { 0.0f, 1.0f, 0.0f };
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Model model = { 0 };
    if (filepath != "" && filepath != "cube" && filepath != "sphere") {
        if (!TryLoadModel(filepath, model)) {
            std::cerr << "Error: Unable to load model from path: " << filepath << '\n';
            filepath = "";
        }
    }

    Vector3 modelPosition = { 0.0f, 0.0f, 0.0f };
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
            } else if (filepath == "sphere") {
                DrawSphere(modelPosition, modelScale, modelTint);
            } else if (model.meshCount == 0) {
                DrawText("Error: Model has no meshes to draw.", 10, 10, 20, RED);
            } else {
                DrawModel(model, modelPosition, modelScale, modelTint);
            }
        EndMode3D();

        if (IsKeyPressed(KEY_O)) {
            std::string newPath = pickModelPath();
            filepath = newPath;

            if (model.meshCount > 0) {
                UnloadModel(model);
                model = { 0 };
            }

            if (filepath != "" && filepath != "cube" && filepath != "sphere") {
                if (!TryLoadModel(filepath, model)) {
                    std::cerr << "Error: Unable to load model from path: " << filepath << '\n';
                    filepath = "";
                }
            }
        }

        if (IsKeyPressed(KEY_C)) {
            selectedColor = (selectedColor + 1) % 4;
            switch (selectedColor) {
                case 0: modelTint = WHITE; break;
                case 1: modelTint = RED; break;
                case 2: modelTint = GREEN; break;
                case 3: modelTint = BLUE; break;
            }
        }

        if (IsKeyPressed(KEY_EQUAL)) {
            modelScale += 0.1f;
        }
        if (IsKeyPressed(KEY_MINUS)) {
            modelScale -= 0.1f;
        }

        if (IsKeyPressed(KEY_ONE)) { selectedCamera = CAMERA_FREE; }
        if (IsKeyPressed(KEY_TWO)) { selectedCamera = CAMERA_ORBITAL; }
        if (IsKeyPressed(KEY_THREE)) { selectedCamera = CAMERA_FIRST_PERSON; }
        if (IsKeyPressed(KEY_FOUR)) { selectedCamera = CAMERA_THIRD_PERSON; }

        DrawText("QuickRay", 20, 20, 24, GREEN);
        DrawText(filepath.c_str(), 20, 50, 18, LIGHTGRAY);
        DrawText("Press O to open file, C to change color,", 20, 80, 12, LIGHTGRAY);
        DrawText("+ or - to scale model", 20, 100, 12, LIGHTGRAY);
        DrawText("Press 1-4 to change camera mode", 20, 120, 12, LIGHTGRAY);
        DrawFPS(20, 135);

        EndDrawing();
    }

    if (model.meshCount > 0) {
        UnloadModel(model);
    }

    CloseWindow();
    return 0;
}
