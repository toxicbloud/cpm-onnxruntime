cmake_minimum_required(VERSION 3.14)

# L'Action GitHub mettra à jour cette ligne automatiquement
set(ORT_VERSION "1.21.0")

project(cpm-onnxruntime VERSION ${ORT_VERSION} LANGUAGES CXX)

# 1. Détection de l'OS
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
    message(FATAL_ERROR "OS non supporté par ce wrapper ONNX Runtime")
endif()

# 2. Détection de l'Architecture
if(CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64|x86_64|amd64")
    set(ORT_ARCH "x64")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64|aarch64|ARM64")
    set(ORT_ARCH "aarch64")
else()
    message(FATAL_ERROR "Architecture ${CMAKE_SYSTEM_PROCESSOR} non supportée")
endif()

# Patch spécifique pour macOS ARM64 (Apple Silicon)
if(ORT_OS STREQUAL "osx" AND ORT_ARCH STREQUAL "aarch64")
    set(ORT_ARCH "arm64")
endif()

# 3. Construction de l'URL officielle de Microsoft
set(ORT_URL "https://github.com/microsoft/onnxruntime/releases/download/v${ORT_VERSION}/onnxruntime-${ORT_OS}-${ORT_ARCH}-${ORT_VERSION}.${ORT_EXT}")

# 4. Téléchargement via FetchContent
include(FetchContent)
FetchContent_Declare(
    onnxruntime_binaries
    URL ${ORT_URL}
)
FetchContent_MakeAvailable(onnxruntime_binaries)

# 5. Création de la cible universelle
if(NOT TARGET onnxruntime)
    add_library(onnxruntime SHARED IMPORTED)
    
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