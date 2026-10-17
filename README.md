# CPM ONNX Runtime

[![Latest release](https://img.shields.io/github/v/release/toxicbloud/cpm-onnxruntime?sort=semver)](https://github.com/toxicbloud/cpm-onnxruntime/releases)
[![Supported platforms](https://img.shields.io/badge/platforms-Linux%20%7C%20macOS%20%7C%20Windows-blue)](#)
[![Release sync](https://github.com/toxicbloud/cpm-onnxruntime/actions/workflows/sync.yml/badge.svg)](https://github.com/toxicbloud/cpm-onnxruntime/actions)
[![MIT license](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)

A small CMake wrapper that downloads the official ONNX Runtime binaries and exposes them as an `onnxruntime` target. Use it with [CPM.cmake](https://github.com/cpm-cmake/CPM.cmake) or CMake's `FetchContent` to add ONNX Runtime to a C++ project.

> This is an independent project. It is not affiliated with, maintained by, or endorsed by Microsoft or the ONNX Runtime team.

## Use with CPM.cmake

Include CPM.cmake in your project, then add the package and link the target:

```cmake
CPMAddPackage("gh:toxicbloud/cpm-onnxruntime@1.31.0")

add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE onnxruntime)
```

The package version selects the ONNX Runtime release. By default, the CPU package is used. Select another backend by setting its CMake variables before adding the package:

```cmake
set(ORT_BACKEND CUDA) # CUDA GPU package
set(ORT_CUDA_VERSION 12) # 12 or 13
CPMAddPackage("gh:toxicbloud/cpm-onnxruntime@1.31.0")
```

`CUDA` packages are available for Linux x64 and Windows x64. macOS and ARM builds use the CPU package. ROCm is not included in the official ONNX Runtime 1.31.0 release archives; to use a compatible ROCm build, provide its archive URL:

```cmake
set(ORT_BACKEND ROCM)
set(ORT_URL "https://example.com/onnxruntime-rocm.tgz")
CPMAddPackage("gh:toxicbloud/cpm-onnxruntime@1.31.0")
```

The custom ROCm archive must have the same `include/` and `lib/` layout expected by this wrapper. See [`example/`](example/) for a complete, buildable project.
