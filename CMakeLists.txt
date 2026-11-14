
cmake_minimum_required(VERSION 3.15)

project(QuickRay LANGUAGES C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Build raylib statically
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

# Include raylib source directly
add_subdirectory(raylib)

# QuickRay executable
add_executable(QuickRay
    main.cpp
    filepicker.h
)

# Link raylib
target_link_libraries(QuickRay PRIVATE raylib)
