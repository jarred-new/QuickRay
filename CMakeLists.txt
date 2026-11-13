
cmake_minimum_required(VERSION 3.15)

project(MyRaylibProject LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

find_package(raylib QUIET)

if(NOT raylib_FOUND)
    add_subdirectory(raylib)
endif()

add_executable(MyRaylibProject
    main.cpp
)

target_link_libraries(MyRaylibProject PRIVATE raylib)
