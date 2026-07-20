cmake_minimum_required(VERSION 3.14)
project(cpm_onnxruntime_example CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. Auto-téléchargement de CPM.cmake ---
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

# --- 2. Utilisation du wrapper ---
# Remplacer 1.18.0 par la version que l'on veut tester
CPMAddPackage("gh:toxicbloud/cpm-onnxruntime@1.27.1")

# --- 3. Création de l'exécutable ---
add_executable(mon_app main.cpp)

# --- 4. Linker ONNX Runtime ---
target_link_libraries(mon_app PRIVATE onnxruntime)