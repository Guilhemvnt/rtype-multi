/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** JsonParser
*/

#include <JsonParser/JsonParser.hpp>

std::string JsonParser::findConfigPath(const std::string& configFilePath) {
    //* Liste des dossiers à rechercher (ajoutez d'autres dossiers au besoin)
    std::vector<std::string> searchPaths = {
        "../../" + configFilePath, // lancer de bin/build
        "../" + configFilePath, // lancer de build
        configFilePath // lancer de la root
    };

    for (const auto& path : searchPaths) {
        std::string fullPath = path;
        if (std::filesystem::exists(fullPath)) {
            return fullPath;
        }
    }

    return "";
}

JsonParser::JsonParser(std::string configPath)
{
    std::ifstream file(findConfigPath(configPath));

    if (!file.is_open()) {
        std::cerr << "[ERROR]: unable to open json file." << std::endl;
        std::cout << findConfigPath(configPath) << " " << configPath << std::endl;
        return;
    }

    Json::parseFromStream(this->_rd, file, &this->_values, nullptr);

    file.close();
}

JsonParser::~JsonParser()
{
}

void JsonParser::GetJsonInfos(const std::string root,  std::map<std::string, std::map<std::string, int>> &infos)
{
    Json::Value entity = this->_values[root];

    for (const auto &category : entity.getMemberNames()) {
        const Json::Value &values = entity[category];

        for (const auto &item : values.getMemberNames()) {
            const std::string &name = item;
            int value = values[name].asInt();
            infos[category][name] = value;
        }
    }
}
