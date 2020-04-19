cmake_minimum_required(VERSION 3.10)

# Define our project
project(Entity3DMath VERSION 1.0)

# Use C++17 for the build
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(EXECUTABLE_OUTPUT_PATH "out")

# Create the target executable
add_executable(
    Entity3DMath
    src/main.cpp
)

# Add the include directories to the target
target_include_directories(
    Entity3DMath PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
)
