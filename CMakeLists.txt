cmake_minimum_required(VERSION 3.14)

# This line is updated automatically by the GitHub Action.
set(ORT_VERSION "1.30.1")

project(cpm-onnxruntime VERSION ${ORT_VERSION} LANGUAGES CXX)

set(ORT_BACKEND "CPU" CACHE STRING "ONNX Runtime backend (CPU, CUDA, or ROCM)")
set_property(CACHE ORT_BACKEND PROPERTY STRINGS CPU CUDA ROCM)
set(ORT_CUDA_VERSION "12" CACHE STRING "CUDA major version for the CUDA backend (12 or 13)")
set_property(CACHE ORT_CUDA_VERSION PROPERTY STRINGS 12 13)
set(ORT_URL "" CACHE STRING "Override the ONNX Runtime archive URL (required for ROCm)")

# 1. Detect the operating system.
if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(ORT_OS "linux")
    set(ORT_EXT "tgz")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(ORT_OS "win")
    set(ORT_EXT "zip")
elseif(CMAKE_SYSTEM_NAME STREQUAL "Darwin")
    set(ORT_OS "osx")
    set(ORT_EXT "tgz")
else()
    message(FATAL_ERROR "Operating system is not supported by this ONNX Runtime wrapper")
endif()

# 2. Detect the architecture.
if(CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64|x86_64|amd64")
    set(ORT_ARCH "x64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64|aarch64|ARM64")
    set(ORT_ARCH "aarch64")
else()
    message(FATAL_ERROR "Architecture ${CMAKE_SYSTEM_PROCESSOR} is not supported")
endif()

# macOS ARM64 (Apple Silicon) uses a different archive architecture name.
if(ORT_OS STREQUAL "osx" AND ORT_ARCH STREQUAL "aarch64")
    set(ORT_ARCH "arm64")
endif()

string(TOUPPER "${ORT_BACKEND}" ORT_BACKEND)
if(NOT ORT_BACKEND MATCHES "^(CPU|CUDA|ROCM)$")
    message(FATAL_ERROR "Unsupported ORT_BACKEND '${ORT_BACKEND}'. Choose CPU, CUDA, or ROCM.")
endif()

if(ORT_BACKEND STREQUAL "CUDA")
    if(NOT ORT_CUDA_VERSION MATCHES "^(12|13)$")
        message(FATAL_ERROR "Unsupported ORT_CUDA_VERSION '${ORT_CUDA_VERSION}'. Choose 12 or 13.")
    endif()
    if(NOT ORT_OS MATCHES "^(linux|win)$" OR NOT ORT_ARCH STREQUAL "x64")
        message(FATAL_ERROR "The CUDA backend is available only for Linux x64 and Windows x64.")
    endif()
elseif(ORT_BACKEND STREQUAL "ROCM")
    if(NOT ORT_OS STREQUAL "linux" OR NOT ORT_ARCH STREQUAL "x64")
        message(FATAL_ERROR "The ROCm backend is available only for Linux x64.")
    endif()
    if(NOT ORT_URL)
        message(FATAL_ERROR "ROCm is not published in the ONNX Runtime ${ORT_VERSION} release archives. Set ORT_URL to a compatible ROCm archive.")
    endif()
endif()

# 3. Build the official Microsoft download URL unless an archive URL was provided.
if(NOT ORT_URL)
    if(ORT_BACKEND STREQUAL "CUDA")
        set(ORT_PACKAGE "gpu_cuda${ORT_CUDA_VERSION}-")
    else()
        set(ORT_PACKAGE "")
    endif()
    set(ORT_URL "https://github.com/microsoft/onnxruntime/releases/download/v${ORT_VERSION}/onnxruntime-${ORT_OS}-${ORT_ARCH}-${ORT_PACKAGE}${ORT_VERSION}.${ORT_EXT}")
endif()

# 4. Download the archive with FetchContent.
include(FetchContent)
FetchContent_Declare(
    onnxruntime_binaries
    URL ${ORT_URL}
)
FetchContent_MakeAvailable(onnxruntime_binaries)

# 5. Create the imported target.
if(NOT TARGET onnxruntime)
    add_library(onnxruntime SHARED IMPORTED GLOBAL)
    
    set_target_properties(onnxruntime PROPERTIES
        INTERFACE_INCLUDE_DIRECTORIES "${onnxruntime_binaries_SOURCE_DIR}/include"
    )

    if(ORT_OS STREQUAL "win")
        set_target_properties(onnxruntime PROPERTIES
            IMPORTED_IMPLIB "${onnxruntime_binaries_SOURCE_DIR}/lib/onnxruntime.lib"
            IMPORTED_LOCATION "${onnxruntime_binaries_SOURCE_DIR}/lib/onnxruntime.dll"
        )
    elseif(ORT_OS STREQUAL "osx")
        set_target_properties(onnxruntime PROPERTIES
            IMPORTED_LOCATION "${onnxruntime_binaries_SOURCE_DIR}/lib/libonnxruntime.dylib"
        )
    else() # Linux
        set_target_properties(onnxruntime PROPERTIES
            IMPORTED_LOCATION "${onnxruntime_binaries_SOURCE_DIR}/lib/libonnxruntime.so"
        )
    endif()
endif()