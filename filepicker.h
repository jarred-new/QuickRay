#ifndef FILEPICKER_H
#define FILEPICKER_H

#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

inline std::string normalizeModelExtension(const std::string& extension) {
    std::string normalized;
    normalized.reserve(extension.size());
    for (unsigned char ch : extension) {
        normalized.push_back(static_cast<char>(std::tolower(ch)));
    }
    return normalized;
}

inline bool isValidModelInput(const std::string& path) {
    if (path.empty()) {
        return false;
    }

    if (path == "cube" || path == "sphere") {
        return true;
    }

    if (!std::filesystem::exists(path) || !std::filesystem::is_regular_file(path)) {
        return false;
    }

    const std::string extension = normalizeModelExtension(std::filesystem::path(path).extension().string());
    return extension == ".obj" || extension == ".glb" || extension == ".gltf";
}

inline std::string pickModelPath() {
    std::string filePath;
    std::cout << "Enter cube, sphere, or a 3D model path (.obj, .glb, .gltf): ";

    if (!std::getline(std::cin >> std::ws, filePath)) {
        std::cerr << "\nInput stream closed. Exiting.\n";
        std::exit(1);
    }

    if (filePath == "cube" || filePath == "sphere") {
        return filePath;
    }

    if (!std::filesystem::exists(filePath) || !std::filesystem::is_regular_file(filePath)) {
        std::cerr << "Error: File not found. Please try again.\n\n";
        return pickModelPath();
    }

    const std::string extension = normalizeModelExtension(std::filesystem::path(filePath).extension().string());
    if (extension != ".obj" && extension != ".glb" && extension != ".gltf") {
        std::cerr << "Error: Invalid file type. Please select a .obj, .glb, or .gltf file.\n\n";
        return pickModelPath();
    }

    return filePath;
}

#endif // FILEPICKER_H
