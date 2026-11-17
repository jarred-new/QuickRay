#include "arguments.h"
#include "filepicker.h"

#include <cerrno>
#include <cmath>
#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

void printUsage(const char* executable) {
    std::cout << "Usage: " << executable
              << " [model-filepath]"
                 " [--color white|red|green|blue]"
                 " [--size positive-number]"
                 " [--camera free|orbital|first-person|third-person]\n";
}

ArgumentParseResult parseArguments(int argc, char* argv[], AppOptions& options) {
    bool modelPathSet = false;

    for (int i = 1; i < argc; ++i) {
        const std::string argument = argv[i];
        if (argument == "--help" || argument == "-h") {
            printUsage(argv[0]);
            return ArgumentParseResult::Help;
        }

        if (argument[0] != '-') {
            if (modelPathSet) {
                std::cerr << "Error: Unexpected positional argument '" << argument << "'.\n";
                printUsage(argv[0]);
                return ArgumentParseResult::Error;
            }

            if (!isValidModelInput(argument)) {
                std::cerr << "Error: Invalid model path '" << argument
                          << "'. Use a valid .obj, .glb, .gltf file or 'cube'/'sphere'.\n";
                printUsage(argv[0]);
                return ArgumentParseResult::Error;
            }

            options.modelFilePath = argument;
            modelPathSet = true;
            continue;
        }

        if (argument == "--color") {
            if (i + 1 >= argc) {
                std::cerr << "Error: --color requires a value.\n";
                printUsage(argv[0]);
                return ArgumentParseResult::Error;
            }

            const std::string value = argv[++i];
            if (value == "white") {
                options.modelTint = WHITE;
                options.selectedColor = 0;
            } else if (value == "red") {
                options.modelTint = RED;
                options.selectedColor = 1;
            } else if (value == "green") {
                options.modelTint = GREEN;
                options.selectedColor = 2;
            } else if (value == "blue") {
                options.modelTint = BLUE;
                options.selectedColor = 3;
            } else {
                std::cerr << "Error: Invalid color '" << value
                          << "'. Choose white, red, green, or blue.\n";
                printUsage(argv[0]);
                return ArgumentParseResult::Error;
            }
        } else if (argument == "--size") {
            if (i + 1 >= argc) {
                std::cerr << "Error: --size requires a value.\n";
                printUsage(argv[0]);
                return ArgumentParseResult::Error;
            }

            const char* value = argv[++i];
            char* end = nullptr;
            errno = 0;
            const float size = std::strtof(value, &end);
            if (end == value || *end != '\0' || errno == ERANGE ||
                !std::isfinite(size) || size <= 0.0f) {
                std::cerr << "Error: --size must be a positive finite number.\n";
                printUsage(argv[0]);
                return ArgumentParseResult::Error;
            }
            options.modelScale = size;
        } else if (argument == "--camera") {
            if (i + 1 >= argc) {
                std::cerr << "Error: --camera requires a value.\n";
                printUsage(argv[0]);
                return ArgumentParseResult::Error;
            }

            const std::string value = argv[++i];
            if (value == "free") {
                options.selectedCamera = CAMERA_FREE;
            } else if (value == "orbital") {
                options.selectedCamera = CAMERA_ORBITAL;
            } else if (value == "first-person") {
                options.selectedCamera = CAMERA_FIRST_PERSON;
            } else if (value == "third-person") {
                options.selectedCamera = CAMERA_THIRD_PERSON;
            } else {
                std::cerr << "Error: Invalid camera '" << value
                          << "'. Choose free, orbital, first-person, or third-person.\n";
                printUsage(argv[0]);
                return ArgumentParseResult::Error;
            }
        } else {
            std::cerr << "Error: Unknown argument '" << argument << "'.\n";
            printUsage(argv[0]);
            return ArgumentParseResult::Error;
        }
    }

    return ArgumentParseResult::Success;
}
