# Minimal C++ example

This example shows how to use ONNX Runtime in a small CMake project with this wrapper and CPM.cmake.

## Requirements

- CMake 3.14 or later
- A C++17 compiler

## Build and run

From this directory, run:

```bash
# Configure the project; CPM downloads ONNX Runtime as part of configuration.
cmake -S . -B build

# Build the example.
cmake --build build

# Run the example.
./build/mon_app