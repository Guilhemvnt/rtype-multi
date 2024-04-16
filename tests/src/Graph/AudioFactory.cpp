/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** AudioFactory
*/

#include <Graph/AudioFactory.hpp>

AudioFactory::AudioFactory(const AudioType type, const std::string& filename)
: parser("src/Graph/GameConfig.json")
{
    _type = type;
    switch (_type) {
        case AudioType::Music:
            if (!music.openFromFile(filename))
                throw Error("Error loading " + filename);
            this->parser.GetJsonInfos("Config", this->parser._parsedData);
            music.setVolume(this->parser._parsedData["Volume"]["Musique"]);
            music.setLoop(true);
            break;
        case AudioType::SoundEffect:
            if (!buffer.loadFromFile(filename))
                throw Error("Error loading " + filename);
            sound.setBuffer(buffer);
            this->parser.GetJsonInfos("Config", this->parser._parsedData);
            sound.setVolume(this->parser._parsedData["Volume"]["Sound"]);
            break;
        default:
            throw Error("unknown audio type");
    }
}

AudioFactory::~AudioFactory()
{
}

void AudioFactory::play()
{
    switch (_type) {
        case AudioType::Music:
            music.play();
            break;
        case AudioType::SoundEffect:
            sound.play();
            break;
        default:
            throw Error("unknown audio type");
    }
}

void AudioFactory::stop()
{
    switch (_type) {
        case AudioType::Music:
            music.stop();
            break;
        case AudioType::SoundEffect:
            sound.stop();
            break;
        default:
            throw Error("unknown audio type");
    }
}

sf::SoundSource::Status AudioFactory::status()
{
    switch (_type) {
        case AudioType::Music:
            return music.getStatus();
        case AudioType::SoundEffect:
            return sound.getStatus();
            break;
        default:
            throw Error("unknown audio type");
    }
}
