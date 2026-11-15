#ifndef FILEPICKER_H
#define FILEPICKER_H

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

std::string pickModelPath() {
    std::string filePath;
    std::cout << "Enter the path to the 3D model (.obj, .glb, .gltf): ";
    
    if (!std::getline(std::cin >> std::ws, filePath)) {
        std::cerr << "\nInput stream closed. Exiting.\n";
        std::exit(1);
    }

    // Validate that the file exists and is not a folder
    if (!std::filesystem::exists(filePath) || !std::filesystem::is_regular_file(filePath)) {
        std::cerr << "Error: File not found. Please try again.\n\n";
        return pickModelPath(); // Recursive call
    }
    else if (filePath == "cube") {
        return "cube"; // Return "cube" for cube model
    }
    else if (filePath == "sphere") {
        return "sphere"; // Return "sphere" for sphere model
    }
    else {
        std::string extension = std::filesystem::path(filePath).extension().string();
        if (extension != ".obj" && extension != ".glb" && extension != ".gltf") {
            std::cerr << "Error: Invalid file type. Please select a .obj, .glb, or .gltf file.\n\n";
            return pickModelPath(); // Recursive call
        }
    }

    return filePath;
}

#endif // FILEPICKER_H
