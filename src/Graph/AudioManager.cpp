/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** AudioManager
*/

#include <Graph/AudioManager.hpp>

AudioManager::AudioManager(std::string assetsPath)
{
    _assetsPath = assetsPath;
}

AudioManager::~AudioManager()
{
}

void AudioManager::createAudio(const std::string& name, const AudioType &type, const std::string& filename) {
    audioMap[name] = std::make_unique<AudioFactory>(type, _assetsPath + "sound/" + filename);
}

std::unique_ptr<AudioFactory> &AudioManager::getAudio(const std::string& name) {
    auto it = audioMap.find(name);
    if (it != audioMap.end())
        return it->second;
    else
        throw Error("Audio not found: " + name);
}
