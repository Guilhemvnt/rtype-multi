/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** main
*/

#include <Graph/Game.hpp>
#include <Error/Error.hpp>
#include <Client/ClientConnection.hpp>

#ifdef __unix__
#include <unistd.h>
#elif defined(_WIN32) || defined(_WIN64)
#include <io.h>
#endif

#include <filesystem>

std::string findFontPath(const std::string& executablePath) {
    //* Liste des dossiers à rechercher (ajoutez d'autres dossiers au besoin)
    std::vector<std::string> searchPaths = {
        executablePath + "/../../src/Client/assets/", // lancer de bin/build
        executablePath + "/../src/Client/assets/", // lancer de build
        executablePath + "/src/Client/assets/", // lancer de la root
        executablePath + "/assets/", // lancer en pkg
    };

    for (const auto& path : searchPaths) {
        std::string fullPath = path;
        if (std::filesystem::exists(fullPath)) {
            return fullPath;
        }
    }

    return "";
}

int main(int argc, char** argv)
{
    (void)argv;

    if (argc != 1) throw Error("Usage: ./client");

    std::string executablePath = std::filesystem::canonical(argv[0]).parent_path().string();
    std::string assetsPath = findFontPath(executablePath);
    if (assetsPath.empty()) {
        throw Error("Assets not found");
    }

    std::unique_ptr<Game> game = std::make_unique<Game>(assetsPath);
    game.get()->run();
    return 0;
}

