# CPM ONNX Runtime Wrapper

[![GitHub Release](https://img.shields.io/github/v/release/toxicbloud/cpm-onnxruntime?sort=semver)](https://github.com/toxicbloud/cpm-onnxruntime/releases)
[![OS Support](https://img.shields.io/badge/OS-Linux%20%7C%20macOS%20%7C%20Windows-blue)](#)
[![Sync Status](https://github.com/toxicbloud/cpm-onnxruntime/actions/workflows/sync.yml/badge.svg)](https://github.com/toxicbloud/cpm-onnxruntime/actions)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

> ⚠️ **Avertissement** : Ce projet **n'est pas** affilié, maintenu ou approuvé par Microsoft ou l'équipe ONNX Runtime. Il s'agit d'un wrapper indépendant créé uniquement pour faciliter l'intégration de la bibliothèque C++ dans des projets via CMake.

---

## 💡 Pourquoi ce dépôt ?

L'équipe d'ONNX Runtime fournit d'excellents [binaires pré-compilés](https://github.com/microsoft/onnxruntime/releases) pour la plupart des architectures. Cependant, ces archives officielles ne contiennent pas de fichier `CMakeLists.txt` natif. 

Résultat : il est fastidieux de les intégrer proprement dans un projet C++ avec des gestionnaires de dépendances modernes comme **[CPM.cmake](https://github.com/cpm-cmake/CPM.cmake)** ou `FetchContent`, car cela demande d'écrire et de maintenir des scripts de téléchargement personnalisés.

**`cpm-onnxruntime` résout ce problème.** C'est un wrapper transparent qui télécharge directement les binaires officiels de Microsoft et expose une cible CMake prête à l'emploi.

## 🚀 Utilisation

Ajoutez simplement ce bloc dans votre `CMakeLists.txt` (assurez-vous d'avoir inclus CPM au préalable). La syntaxe courte de CPM permet une intégration en une seule ligne :

```cmake
# 1. Télécharger ONNX Runtime via ce wrapper (remplacez 1.18.0 par la version souhaitée)
CPMAddPackage("gh:toxicbloud/cpm-onnxruntime@1.18.0")

# 2. Créer votre cible
add_executable(mon_app main.cpp)

# 3. Lier ONNX Runtime
target_link_libraries(mon_app PRIVATE onnxruntime)