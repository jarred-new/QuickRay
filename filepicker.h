#ifndef FILEPICKER_H
#define FILEPICKER_H

#include <iostream>
#include <fstream>
#include <string>

void pick(char* v) {
    if (v == nullptr) {
        return;
    }
    
    std::cout << "Enter your model filename: ";
    if (!(std::cin >> v)) {
        return;
    }
}

#endif // FILEPICKER_H