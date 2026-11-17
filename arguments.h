#ifndef ARGUMENTS_H
#define ARGUMENTS_H

#include "raylib.h"

#include <string>

struct AppOptions {
    float modelScale = 1.0f;
    Color modelTint = WHITE;
    int selectedColor = 0;
    int selectedCamera = CAMERA_FREE;
    std::string modelFilePath;
};

enum class ArgumentParseResult {
    Success,
    Help,
    Error
};

ArgumentParseResult parseArguments(int argc, char* argv[], AppOptions& options);
void printUsage(const char* executable);

#endif // ARGUMENTS_H
