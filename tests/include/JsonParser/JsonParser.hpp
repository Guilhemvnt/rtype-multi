/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** JsonParser
*/

#pragma once

#include <map>
#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <json/json.h>

class JsonParser {
    public:
        JsonParser(std::string configPath);
        ~JsonParser();

        void GetJsonInfos(std::string, std::map<std::string, std::map<std::string, int>> &);

            // values holding
            std::map<std::string, std::map<std::string, int>> _parsedData;
    private:
        std::string findConfigPath(const std::string& configFilePath);
    protected:
            // file parsing
            Json::Value _values; // contains the values of the json file
            Json::CharReaderBuilder _rd; // used to read the json file (not useful otherwise)
};
