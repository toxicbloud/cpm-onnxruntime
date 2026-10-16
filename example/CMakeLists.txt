cmake_minimum_required(VERSION 3.14)
project(cpm_onnxruntime_example CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. Download CPM.cmake if needed ---
set(CPM_DOWNLOAD_VERSION 0.40.0)
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM_${CPM_DOWNLOAD_VERSION}.cmake")
if(NOT (EXISTS ${CPM_DOWNLOAD_LOCATION}))
    message(STATUS "Downloading CPM.cmake to ${CPM_DOWNLOAD_LOCATION}")
    file(DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v${CPM_DOWNLOAD_VERSION}/CPM.cmake
        ${CPM_DOWNLOAD_LOCATION}
    )
endif()
include(${CPM_DOWNLOAD_LOCATION})

# --- 2. Add the wrapper ---
CPMAddPackage("gh:toxicbloud/cpm-onnxruntime@1.31.0")

# --- 3. Create the executable ---
add_executable(mon_app main.cpp)

# --- 4. Link ONNX Runtime ---
target_link_libraries(mon_app PRIVATE onnxruntime)