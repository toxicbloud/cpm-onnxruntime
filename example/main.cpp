#include <iostream>
#include <onnxruntime_cxx_api.h>

int main() {
    std::cout << "=== Test CPM ONNX Runtime ===" << std::endl;

    try {
        // 1. Initialize the environment (required by ONNX Runtime).
        Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "CPM_Test_Env");
        
        // 2. Print the version to confirm that dynamic linking worked.
        std::cout << "ONNX Runtime initialized successfully." << std::endl;
        std::cout << "API version: " << OrtGetApiBase()->GetVersionString() << std::endl;

        // 3. Set up basic session options.
        Ort::SessionOptions session_options;
        session_options.SetIntraOpNumThreads(1);
        session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);

        std::cout << "Ready to load a model and run inference." << std::endl;

    } catch (const Ort::Exception& e) {
        std::cerr << "ONNX Runtime error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}