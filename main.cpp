// Build & run: c++ main.cpp -o app -lraylib && ./app
// Note: needs a display. Opens an 800x450 window until closed.
#include "raylib.h"

int main() {
    InitWindow(800, 450, "Raylib C++ Starter");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GREEN);
        DrawText("Hello from raylib in C++!", 220, 200, 24, DARKGRAY);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
