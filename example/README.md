# Exemple d'utilisation de CPM ONNX Runtime

Cet exemple montre comment configurer un projet CMake minimal pour utiliser ONNX Runtime via notre wrapper CPM.

## Prérequis
* CMake 3.14+
* Un compilateur C++17

## Compiler et exécuter

Ouvrez un terminal dans ce dossier (`example/`) et lancez :

```bash
# 1. Générer les fichiers de build (CPM téléchargera ONNX Runtime automatiquement ici)
cmake -S . -B build

# 2. Compiler le projet
cmake --build build

# 3. Exécuter l'application
./build/mon_app