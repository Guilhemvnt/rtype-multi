/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** ObjectFactory
*/

#ifndef OBJECTFACTORY_HPP_
#define OBJECTFACTORY_HPP_

#include <Graph/GameObject.hpp>
#include <JsonParser/JsonParser.hpp>

class ObjectFactory {
protected:
private:
    JsonParser parser;
public:
    ObjectFactory(std::string assetsPath);
    ~ObjectFactory() = default;

    std::shared_ptr<GameObject> createObject(std::string type, int);
    std::string assetsPath;
    sf::Texture textureUI;
    sf::Texture textureShip;
    sf::Texture textureBullet;
    sf::Texture textureEnemy;
};

#endif /* !OBJECTFACTORY_HPP_ */
