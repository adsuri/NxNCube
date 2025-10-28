cmake_minimum_required(VERSION 3.16)

project(NxNCube LANGUAGES CXX)

# Explicitly use g++
set(CMAKE_CXX_COMPILER g++)

# Compiler flags (copied from your Makefile)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror -pedantic -g -Wno-sign-compare -Wno-comment -fsanitize=address -fsanitize=undefined -D_GLIBCXX_DEBUG")

# Define your executable and source files
add_executable(nxncube
    src/game.cpp
    src/NxNCube.cpp
)

# Output to the *source tree’s* build/ folder
set_target_properties(nxncube PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/build"
)
