#include <iostream>
#include <onnxruntime_cxx_api.h>

int main() {
    std::cout << "=== Test CPM ONNX Runtime ===" << std::endl;

    try {
        // 1. Initialiser l'environnement (Requis par ONNX Runtime)
        Ort::Env env(ORT_LOGGING_LEVEL_WARNING, "CPM_Test_Env");
        
        // 2. Afficher la version pour prouver que le linkage dynamique a fonctionné
        std::cout << "✅ ONNX Runtime charge avec succes !" << std::endl;
        std::cout << "🏷️  Version de l'API : " << OrtGetApiBase()->GetVersionString() << std::endl;

        // 3. Préparer les options de session (Exemple basique)
        Ort::SessionOptions session_options;
        session_options.SetIntraOpNumThreads(1);
        session_options.SetGraphOptimizationLevel(GraphOptimizationLevel::ORT_ENABLE_EXTENDED);

        std::cout << "🚀 Pret a charger un modele et faire une inference !" << std::endl;

    } catch (const Ort::Exception& e) {
        std::cerr << "❌ Erreur ONNX Runtime : " << e.what() << std::endl;
        return 1;
    }

    return 0;
}