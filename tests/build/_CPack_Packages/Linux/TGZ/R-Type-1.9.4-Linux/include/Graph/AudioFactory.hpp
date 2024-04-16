/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** AudioFactory
*/

#pragma once

#include <SFML/Audio.hpp>
#include <Error/Error.hpp>
#include <iostream>
#include <JsonParser/JsonParser.hpp>

enum class AudioType {
    Music,
    SoundEffect
};

class AudioFactory {
    public:

        AudioFactory(const AudioType type, const std::string& filename);
        ~AudioFactory();

        void play();
        void stop();
        sf::SoundSource::Status status();

    private:
        JsonParser parser;
        AudioType _type;
        sf::Music music;
        sf::SoundBuffer buffer;
        sf::Sound sound;
};
