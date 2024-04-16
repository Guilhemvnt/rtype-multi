/*
** EPITECH PROJECT, 2023
** B-CPP-550-LYN-5-2-rtype-erwann.laplante
** File description:
** ObjectFactory
*/

#include <Graph/ObjectFactory.hpp>

ObjectFactory::ObjectFactory(std::string assetsPath)
: parser("src/Graph/GameConfig.json")
{
    this->assetsPath = assetsPath;
    if (!textureUI.loadFromFile(assetsPath))
        std::cout << "Error loading UI texture" << std::endl;
        return;
}

std::shared_ptr<GameObject> ObjectFactory::createObject(std::string type, int nb_Entity)
{
    std::shared_ptr<GameObject> object = std::make_shared<GameObject>();
    if (type == "entity") {
        object->id = nb_Entity;
        object->sprite.setTexture(textureUI);
        object->sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
    }
    if (type == "planet1") {
        object->id = nb_Entity;
        object->nbFrames = 49;
        object->sprite.setTexture(textureUI);
        object->sprite.setPosition(sf::Vector2f(-80, 470));
        object->sprite.setTextureRect(sf::IntRect(0, 0, 100, 100));
        object->sprite.setScale(sf::Vector2f(800 / 80, 600 / 100));
        sf::Color color(150, 150, 150);
        object->sprite.setColor(color);
    }
    if (type == "explosion") {
        object->id = nb_Entity;
        object->nbFrames = 4;
        object->sprite.setTexture(textureUI);
        object->sprite.setTextureRect(sf::IntRect(0, 113, 16, 14));
    }
    if (type == "HUD0" || type == "HUD1" || type == "HUD2" || type == "HUD3") {
        std::cout << type << std::endl;
        int nbHUD = std::stoi(type.substr(3, 1));
        object->id = nb_Entity;
        object->sprite.setTexture(textureUI);
        object->sprite.setTextureRect(sf::IntRect(0, 57, 28, 13));
        object->sprite.setPosition(sf::Vector2f(0 + (nbHUD * 28 * 4), 550));
        object->sprite.setScale(sf::Vector2f(4, 4));

        object->healthBar.setSize(sf::Vector2f(104, 12));
        object->healthBar.setFillColor(sf::Color{100, 27, 27});
        switch (nbHUD) {
            case 0:
                object->healthBar.setFillColor(sf::Color{225, 226, 21});
                break;
            case 1:
                object->healthBar.setFillColor(sf::Color{31, 150, 24});
                break;
            case 2:
                object->healthBar.setFillColor(sf::Color{27, 48, 226});
                break;
            case 3:
                object->healthBar.setFillColor(sf::Color{255, 70, 70});
                break;
            default:
                object->healthBar.setFillColor(sf::Color{100, 27, 27});
                break;
        }
        object->healthBar.setPosition(sf::Vector2f(object->sprite.getPosition().x + 4, object->sprite.getPosition().y + 20));

        object->backgroundHealthBar.setSize(sf::Vector2f(104, 11));
        object->backgroundHealthBar.setFillColor(sf::Color{255, 255, 255});
        object->backgroundHealthBar.setPosition(sf::Vector2f(object->sprite.getPosition().x + 4, object->sprite.getPosition().y + 21));
        object->backgroundHealthBar.setOutlineColor(sf::Color{0, 0, 0});
        object->backgroundHealthBar.setOutlineThickness(2);

        object->powerBar.setSize(sf::Vector2f(0, 12));

        this->parser.GetJsonInfos("Color", this->parser._parsedData);

        object->powerBar.setFillColor(sf::Color(this->parser._parsedData["powerBar"]["red"],
            this->parser._parsedData["powerBar"]["green"],
            this->parser._parsedData["powerBar"]["blue"]));

        object->powerBar.setPosition(sf::Vector2f(object->sprite.getPosition().x + 24, object->sprite.getPosition().y +36));

        object->backgroundPowerBar.setSize(sf::Vector2f(76, 12));
        object->backgroundPowerBar.setFillColor(sf::Color{255, 255, 255});
        object->backgroundPowerBar.setPosition(sf::Vector2f(object->sprite.getPosition().x + 24, object->sprite.getPosition().y +36));
    }
    return object;
}
