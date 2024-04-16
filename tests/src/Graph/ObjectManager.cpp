/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** ObjectManager
*/

#include <Graph/ObjectManager.hpp>

void ObjectManager::addObject(std::shared_ptr<GameObject> object)
{
    this->objects[object->id] = object;
}

void ObjectManager::createObject(std::string type, int id)
{
    this->objects[id] = objectFactory->createObject(type, id);
}

void ObjectManager::removeObject(int id)
{
    if (this->objects.find(id) != this->objects.end())
        this->objects.erase(id);
}

void ObjectManager::updateObjects(float deltaTime, std::map<int, std::vector<int>> updateData)
{
    for (auto [id, data] : updateData) {
        if (objects[id] == nullptr) {
            objects[id] = objectFactory->createObject("entity", id);
            objects[id]->sprite.setPosition(sf::Vector2f(data[0], data[1]));
        } else {
            objects[id]->sprite.setPosition(sf::Vector2f(data[0], data[1]));
        }
    }
}

void ObjectManager::renderObjects(sf::RenderWindow& window)
{
    for (auto& [id, object] : this->objects) {
        object->animate(updateTime);
        object->render(window);
    }
}

void ObjectManager::setTextureRect(int id, int w, int h, enum type t, int playerId)
{
    if (this->objects.find(id) == this->objects.end())
    {
        std::cerr << "Invalid object ID or object pointer is nullptr." << std::endl;
        return;
    }
    this->objects[id]->type = t;
    if (t == defaultType) {
        return;
    }
    if (t == enemy) {
        this->parser.GetJsonInfos("AI", this->parser._parsedData);
        this->objects[id]->nbFrames = this->parser._parsedData["Frame"]["nbrFrame"];
        this->objects[id]->sprite.setTextureRect(sf::IntRect(
            this->parser._parsedData["Sprite"]["left"],
            this->parser._parsedData["Sprite"]["top"],
            this->parser._parsedData["Sprite"]["width"],
            this->parser._parsedData["Sprite"]["height"]));
    }
    if (t == player) {
        this->parser.GetJsonInfos("Player", this->parser._parsedData);
        this->objects[id]->sprite.setTextureRect(sf::IntRect(
            this->parser._parsedData["Sprite"]["left"] + (playerId * (this->parser._parsedData["Sprite"]["width"] + 2)),
            this->parser._parsedData["Sprite"]["top"],
            this->parser._parsedData["Sprite"]["width"],
            this->parser._parsedData["Sprite"]["height"]));
    }
    if (t == bullet0) {
        this->parser.GetJsonInfos("Bullet0", this->parser._parsedData);
        this->objects[id]->nbFrames = this->parser._parsedData["Frame"]["nbrFrame"];
        this->objects[id]->sprite.setTextureRect(sf::IntRect(
            this->parser._parsedData["Sprite"]["left"],
            this->parser._parsedData["Sprite"]["top"],
            this->parser._parsedData["Sprite"]["width"],
            this->parser._parsedData["Sprite"]["height"]));
    }
    if (t == bullet1) {
        this->parser.GetJsonInfos("Bullet1", this->parser._parsedData);
        this->objects[id]->nbFrames = this->parser._parsedData["Frame"]["nbrFrame"];
        this->objects[id]->sprite.setTextureRect(sf::IntRect(
            this->parser._parsedData["Sprite"]["left"],
            this->parser._parsedData["Sprite"]["top"],
            this->parser._parsedData["Sprite"]["width"],
            this->parser._parsedData["Sprite"]["height"]));
        this->objects[id]->sprite.setColor(sf::Color(
            this->parser._parsedData["Color"]["red"],
            this->parser._parsedData["Color"]["green"],
            this->parser._parsedData["Color"]["blue"]));
    }
    if (t == bullet2) {
        this->parser.GetJsonInfos("Bullet2", this->parser._parsedData);
        this->objects[id]->nbFrames = this->parser._parsedData["Frame"]["nbrFrame"];
        this->objects[id]->sprite.setTextureRect(sf::IntRect(
            this->parser._parsedData["Sprite"]["left"],
            this->parser._parsedData["Sprite"]["top"],
            this->parser._parsedData["Sprite"]["width"],
            this->parser._parsedData["Sprite"]["height"]));
        this->objects[id]->sprite.setColor(sf::Color(
            this->parser._parsedData["Color"]["red"],
            this->parser._parsedData["Color"]["green"],
            this->parser._parsedData["Color"]["blue"]));
    }
    if (t == bullet3) {
        this->parser.GetJsonInfos("Bullet3", this->parser._parsedData);
        this->objects[id]->nbFrames = this->parser._parsedData["Frame"]["nbrFrame"];
        this->objects[id]->sprite.setTextureRect(sf::IntRect(
            this->parser._parsedData["Sprite"]["left"],
            this->parser._parsedData["Sprite"]["top"],
            this->parser._parsedData["Sprite"]["width"],
            this->parser._parsedData["Sprite"]["height"]));
    }
    if (t == bullet4) {
        this->parser.GetJsonInfos("Bullet4", this->parser._parsedData);
        this->objects[id]->nbFrames = this->parser._parsedData["Frame"]["nbrFrame"];
        this->objects[id]->sprite.setTextureRect(sf::IntRect(
            this->parser._parsedData["Sprite"]["left"],
            this->parser._parsedData["Sprite"]["top"],
            this->parser._parsedData["Sprite"]["width"],
            this->parser._parsedData["Sprite"]["height"]));
        this->objects[id]->sprite.setColor(sf::Color(
            this->parser._parsedData["Color"]["red"],
            this->parser._parsedData["Color"]["green"],
            this->parser._parsedData["Color"]["blue"]));
    }
    if (t == boss) {
        this->parser.GetJsonInfos("Boss", this->parser._parsedData);
        this->objects[id]->nbFrames = this->parser._parsedData["Frame"]["nbrFrame"];
        this->objects[id]->sprite.setTextureRect(sf::IntRect(
            this->parser._parsedData["Sprite"]["left"],
            this->parser._parsedData["Sprite"]["top"],
            this->parser._parsedData["Sprite"]["width"],
            this->parser._parsedData["Sprite"]["height"]));
    }
    if (t == bossBullet) {
        this->parser.GetJsonInfos("BossBullet", this->parser._parsedData);
        this->objects[id]->nbFrames = this->parser._parsedData["Frame"]["nbrFrame"];
        this->objects[id]->sprite.setTextureRect(sf::IntRect(
            this->parser._parsedData["Sprite"]["left"],
            this->parser._parsedData["Sprite"]["top"],
            this->parser._parsedData["Sprite"]["width"],
            this->parser._parsedData["Sprite"]["height"]));
    }
    if (t == rocket) {
        this->parser.GetJsonInfos("Rocket", this->parser._parsedData);
        this->objects[id]->nbFrames = this->parser._parsedData["Frame"]["nbrFrame"];
        this->objects[id]->sprite.setTextureRect(sf::IntRect(
            this->parser._parsedData["Sprite"]["left"],
            this->parser._parsedData["Sprite"]["top"],
            this->parser._parsedData["Sprite"]["width"],
            this->parser._parsedData["Sprite"]["height"]));
    }
    if (t == PowerUpHealth) {
        this->parser.GetJsonInfos("PowerUpHealth", this->parser._parsedData);
        this->objects[id]->nbFrames = this->parser._parsedData["Frame"]["nbrFrame"];
        this->objects[id]->sprite.setTextureRect(sf::IntRect(
            this->parser._parsedData["Sprite"]["left"],
            this->parser._parsedData["Sprite"]["top"],
            this->parser._parsedData["Sprite"]["width"],
            this->parser._parsedData["Sprite"]["height"]));
    }
    if (t == PowerUpSpeed) {
        this->parser.GetJsonInfos("PowerUpSpeed", this->parser._parsedData);
        this->objects[id]->nbFrames = this->parser._parsedData["Frame"]["nbrFrame"];
        this->objects[id]->sprite.setTextureRect(sf::IntRect(
            this->parser._parsedData["Sprite"]["left"],
            this->parser._parsedData["Sprite"]["top"],
            this->parser._parsedData["Sprite"]["width"],
            this->parser._parsedData["Sprite"]["height"]));
        this->objects[id]->sprite.setColor(sf::Color(
            this->parser._parsedData["Color"]["red"],
            this->parser._parsedData["Color"]["green"],
            this->parser._parsedData["Color"]["blue"]));
    }
    if (t == PowerUpDamage) {
        this->parser.GetJsonInfos("PowerUpDamage", this->parser._parsedData);
        this->objects[id]->nbFrames = this->parser._parsedData["Frame"]["nbrFrame"];
        this->objects[id]->sprite.setTextureRect(sf::IntRect(
            this->parser._parsedData["Sprite"]["left"],
            this->parser._parsedData["Sprite"]["top"],
            this->parser._parsedData["Sprite"]["width"],
            this->parser._parsedData["Sprite"]["height"]));
        this->objects[id]->sprite.setColor(sf::Color(
            this->parser._parsedData["Color"]["red"],
            this->parser._parsedData["Color"]["green"],
            this->parser._parsedData["Color"]["blue"]));
    }
    if (t == PowerUpDoubleShoot) {
        this->parser.GetJsonInfos("PowerUpDoubleShoot", this->parser._parsedData);
        this->objects[id]->nbFrames = this->parser._parsedData["Frame"]["nbrFrame"];
        this->objects[id]->sprite.setTextureRect(sf::IntRect(
            this->parser._parsedData["Sprite"]["left"],
            this->parser._parsedData["Sprite"]["top"],
            this->parser._parsedData["Sprite"]["width"],
            this->parser._parsedData["Sprite"]["height"]));
        this->objects[id]->sprite.setColor(sf::Color(
            this->parser._parsedData["Color"]["red"],
            this->parser._parsedData["Color"]["green"],
            this->parser._parsedData["Color"]["blue"]));
    }
    if (t == PowerUpRocketShoot) {
        this->parser.GetJsonInfos("PowerUpRocketShoot", this->parser._parsedData);
        this->objects[id]->nbFrames = this->parser._parsedData["Frame"]["nbrFrame"];
        this->objects[id]->sprite.setTextureRect(sf::IntRect(
            this->parser._parsedData["Sprite"]["left"],
            this->parser._parsedData["Sprite"]["top"],
            this->parser._parsedData["Sprite"]["width"],
            this->parser._parsedData["Sprite"]["height"]));
        this->objects[id]->sprite.setColor(sf::Color(
            this->parser._parsedData["Color"]["red"],
            this->parser._parsedData["Color"]["green"],
            this->parser._parsedData["Color"]["blue"]));
    }
    this->objects[id]->sprite.setScale(
        w / this->objects[id]->sprite.getLocalBounds().width,
        h / this->objects[id]->sprite.getLocalBounds().height
    );
}

void ObjectManager::setColorHeatlh(int id, sf::Color color)
{
    if (this->objects.find(id) == this->objects.end())
    {
        std::cerr << "Invalid object ID or object pointer is nullptr." << std::endl;
        return;
    }

    if (id >= 0 && id < this->objects.size() && this->objects[id] != nullptr)
    {
        std::cout << "set color " << id << std::endl;
        this->objects[id]->healthBar.setFillColor(color);
    }
    else
    {
        std::cerr << "Invalid object ID or object pointer is nullptr." << std::endl;
    }
}

void ObjectManager::updateStatBar(int id, int x, std::string type)
{
    if (objects.find(id) != this->objects.end()) {
        if (type == "power" && x <= 4)
        {
            this->objects[id]->powerBar.setSize(sf::Vector2f(x * 19, this->objects[id]->powerBar.getSize().y));
        }
        if (type == "health")
        {
            this->objects[id]->healthBar.setSize(sf::Vector2f(x, this->objects[id]->healthBar.getSize().y));
        }
    }
}


void ObjectManager::setHealth(int id, int health)
{
    if (this->objects.find(id) != this->objects.end())
        this->objects[id]->health = health;
}