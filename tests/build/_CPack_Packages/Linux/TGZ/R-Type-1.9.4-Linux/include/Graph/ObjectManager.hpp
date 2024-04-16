/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** ObjectManager
*/

#ifndef OBJECTMANAGER_HPP_
#define OBJECTMANAGER_HPP_

#include <memory>
#include <vector>
#include <Graph/GameObject.hpp>
#include <Graph/ObjectFactory.hpp>
#include <JsonParser/JsonParser.hpp>

class ObjectManager {
    public:
        ObjectManager(std::string assetsPath)
            : objectFactory(std::make_shared<ObjectFactory>(assetsPath)),
            parser("src/Graph/AssetsConfig.json")
            {};
        void setTextureRect(int id, int w, int h, enum type t, int playerId);
        void setHealth(int id, int health);
        void addObject(std::shared_ptr<GameObject> object);
        void createObject(std::string type, int id);
        void removeObject(int id);
        void updateObjects(float, std::map<int, std::vector<int>>);
        void renderObjects(sf::RenderWindow& window);

        void updateStatBar(int id, int x, std::string type);
        void setColorHeatlh(int id, sf::Color color);


        std::map<int, std::shared_ptr<GameObject>> objects;

        std::shared_ptr<ObjectFactory> objectFactory;
        sf::Time updateTime;
    private:
        JsonParser parser;
};

#endif /* !OBJECTMANAGER_HPP_ */
