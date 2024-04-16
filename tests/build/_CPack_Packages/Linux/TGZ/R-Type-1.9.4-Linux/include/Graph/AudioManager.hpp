/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** AudioManager
*/

#pragma once

#include <Graph/AudioFactory.hpp>
#include <map>

class AudioManager {
    public:
        AudioManager(std::string assetsPath);
        ~AudioManager();
        void createAudio(const std::string& name, const AudioType &type, const std::string& filename);

        std::unique_ptr<AudioFactory> &getAudio(const std::string& name);

    private:
        std::string _assetsPath;
        std::map<std::string, std::unique_ptr<AudioFactory>> audioMap;
};
