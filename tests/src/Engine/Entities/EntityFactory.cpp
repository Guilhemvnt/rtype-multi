/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rTypeEntity-erwann.laplante
** File description:
** EntityFactory
*/

#include <Engine/Entities/EntityFactory.hpp>

#if defined(_WIN32) || defined(_WIN64)
    #pragma warning(disable: 4244)
#endif

EntityFactory::EntityFactory(void)
: parser("src/Engine/EntityConfig.json")
{
}

EntityFactory::~EntityFactory() { }

Entity& EntityFactory::createEntity(std::string name)
{
    auto* entity = new Entity();

    if (name == "Player") {
        this->parser.GetJsonInfos("Player", this->parser._parsedData);
        entity->createComponent<TypeEntity>(player);
        entity->createComponent<Input>(0, 0, false, false);
        entity->createComponent<Position>(
            this->parser._parsedData["Position"]["x"],
            this->parser._parsedData["Position"]["y"],
            this->parser._parsedData["Position"]["z"],
            this->parser._parsedData["Position"]["speed"]
        );
        entity->createComponent<Collider>(
            this->parser._parsedData["Collider"]["width"],
            this->parser._parsedData["Collider"]["height"],
            this->parser._parsedData["Collider"]["layer"]
        );
        entity->createComponent<Health>(
            this->parser._parsedData["Health"]["life"],
            this->parser._parsedData["Health"]["maxHealth"]
        );
        entity->createComponent<Weapon>(
            "Player",
            this->parser._parsedData["Weapon"]["damage"],
            this->parser._parsedData["Weapon"]["ammo"]
        );
    } else if (name == "AI") {
        this->parser.GetJsonInfos("AI", this->parser._parsedData);
        entity->createComponent<TypeEntity>(enemy);
        entity->createComponent<Input>(-1, 0, true, true);
        entity->createComponent<Position>(
            this->parser._parsedData["Position"]["x"],
            this->parser._parsedData["Position"]["y"],
            this->parser._parsedData["Position"]["z"],
            this->parser._parsedData["Position"]["speed"]
        );
        entity->createComponent<Collider>(
            this->parser._parsedData["Collider"]["width"],
            this->parser._parsedData["Collider"]["height"],
            this->parser._parsedData["Collider"]["layer"]
        );
        entity->createComponent<Health>(
            this->parser._parsedData["Health"]["life"],
            this->parser._parsedData["Health"]["maxHealth"]
        );
        entity->createComponent<Weapon>(
            "AI",
            this->parser._parsedData["Weapon"]["damage"],
            this->parser._parsedData["Weapon"]["ammo"]
        );
    } else if (name == "Boss") {
        this->parser.GetJsonInfos("Boss", this->parser._parsedData);
        entity->createComponent<TypeEntity>(boss);
        entity->createComponent<Input>(0, 0, true, true);
        entity->createComponent<Position>(
            this->parser._parsedData["Position"]["x"],
            this->parser._parsedData["Position"]["y"],
            this->parser._parsedData["Position"]["z"],
            this->parser._parsedData["Position"]["speed"]
        );
        entity->createComponent<Collider>(
            this->parser._parsedData["Collider"]["width"],
            this->parser._parsedData["Collider"]["height"],
            this->parser._parsedData["Collider"]["layer"]
        );
        entity->createComponent<Health>(
            this->parser._parsedData["Health"]["life"],
            this->parser._parsedData["Health"]["maxHealth"]
        );
        entity->createComponent<Weapon>(
            "Boss",
            this->parser._parsedData["Weapon"]["damage"],
            this->parser._parsedData["Weapon"]["ammo"]
        );
    } else if (name == "Block") {
        this->parser.GetJsonInfos("Block", this->parser._parsedData);
        entity->createComponent<TypeEntity>(block);
        entity->createComponent<Input>(0, 0, true, false);
        entity->createComponent<Position>(
            this->parser._parsedData["Position"]["x"],
            this->parser._parsedData["Position"]["y"],
            this->parser._parsedData["Position"]["z"],
            this->parser._parsedData["Position"]["speed"]
        );
        entity->createComponent<Collider>(
            this->parser._parsedData["Collider"]["width"],
            this->parser._parsedData["Collider"]["height"],
            this->parser._parsedData["Collider"]["layer"]
        );
        entity->createComponent<Health>(
            this->parser._parsedData["Health"]["life"],
            this->parser._parsedData["Health"]["maxHealth"]
        );
        entity->createComponent<Weapon>(
            "Block",
            this->parser._parsedData["Weapon"]["damage"],
            this->parser._parsedData["Weapon"]["ammo"]
        );
    } else if (name == "Bullet0") {
        this->parser.GetJsonInfos("Bullet0", this->parser._parsedData);
        entity->createComponent<TypeEntity>(bullet0);
        entity->createComponent<Input>(0, 0, false, true);
        entity->createComponent<Position>(
            this->parser._parsedData["Position"]["x"],
            this->parser._parsedData["Position"]["y"],
            this->parser._parsedData["Position"]["z"],
            this->parser._parsedData["Position"]["speed"]
        );
        entity->createComponent<Collider>(
            this->parser._parsedData["Collider"]["width"],
            this->parser._parsedData["Collider"]["height"],
            this->parser._parsedData["Collider"]["layer"]
        );
        entity->createComponent<Health>(
            this->parser._parsedData["Health"]["life"],
            this->parser._parsedData["Health"]["maxHealth"]
        );
        entity->createComponent<Weapon>(
            "Bullet",
            this->parser._parsedData["Weapon"]["damage"],
            this->parser._parsedData["Weapon"]["ammo"]
        );
    } else if (name == "Bullet1") {
        this->parser.GetJsonInfos("Bullet1", this->parser._parsedData);
        entity->createComponent<TypeEntity>(bullet1);
        entity->createComponent<Input>(0, 0, false, true);
        entity->createComponent<Position>(
            this->parser._parsedData["Position"]["x"],
            this->parser._parsedData["Position"]["y"],
            this->parser._parsedData["Position"]["z"],
            this->parser._parsedData["Position"]["speed"]
        );
        entity->createComponent<Collider>(
            this->parser._parsedData["Collider"]["width"],
            this->parser._parsedData["Collider"]["height"],
            this->parser._parsedData["Collider"]["layer"]
        );
        entity->createComponent<Health>(
            this->parser._parsedData["Health"]["life"],
            this->parser._parsedData["Health"]["maxHealth"]
        );
        entity->createComponent<Weapon>(
            "Bullet",
            this->parser._parsedData["Weapon"]["damage"],
            this->parser._parsedData["Weapon"]["ammo"]
        );
    } else if (name == "Bullet2") {
        this->parser.GetJsonInfos("Bullet2", this->parser._parsedData);
        entity->createComponent<TypeEntity>(bullet2);
        entity->createComponent<Input>(0, 0, false, true);
        entity->createComponent<Position>(
            this->parser._parsedData["Position"]["x"],
            this->parser._parsedData["Position"]["y"],
            this->parser._parsedData["Position"]["z"],
            this->parser._parsedData["Position"]["speed"]
        );
        entity->createComponent<Collider>(
            this->parser._parsedData["Collider"]["width"],
            this->parser._parsedData["Collider"]["height"],
            this->parser._parsedData["Collider"]["layer"]
        );
        entity->createComponent<Health>(
            this->parser._parsedData["Health"]["life"],
            this->parser._parsedData["Health"]["maxHealth"]
        );
        entity->createComponent<Weapon>(
            "Bullet",
            this->parser._parsedData["Weapon"]["damage"],
            this->parser._parsedData["Weapon"]["ammo"]
        );
    } else if (name == "Bullet3") {
        this->parser.GetJsonInfos("Bullet3", this->parser._parsedData);
        entity->createComponent<TypeEntity>(bullet3);
        entity->createComponent<Input>(0, 0, false, true);
        entity->createComponent<Position>(
            this->parser._parsedData["Position"]["x"],
            this->parser._parsedData["Position"]["y"],
            this->parser._parsedData["Position"]["z"],
            this->parser._parsedData["Position"]["speed"]
        );
        entity->createComponent<Collider>(
            this->parser._parsedData["Collider"]["width"],
            this->parser._parsedData["Collider"]["height"],
            this->parser._parsedData["Collider"]["layer"]
        );
        entity->createComponent<Health>(
            this->parser._parsedData["Health"]["life"],
            this->parser._parsedData["Health"]["maxHealth"]
        );
        entity->createComponent<Weapon>(
            "Bullet",
            this->parser._parsedData["Weapon"]["damage"],
            this->parser._parsedData["Weapon"]["ammo"]
        );
    } else if (name == "Bullet4") {
        this->parser.GetJsonInfos("Bullet4", this->parser._parsedData);
        entity->createComponent<TypeEntity>(bullet4);
        entity->createComponent<Input>(0, 0, false, true);
        entity->createComponent<Position>(
            this->parser._parsedData["Position"]["x"],
            this->parser._parsedData["Position"]["y"],
            this->parser._parsedData["Position"]["z"],
            this->parser._parsedData["Position"]["speed"]
        );
        entity->createComponent<Collider>(
            this->parser._parsedData["Collider"]["width"],
            this->parser._parsedData["Collider"]["height"],
            this->parser._parsedData["Collider"]["layer"]
        );
        entity->createComponent<Health>(
            this->parser._parsedData["Health"]["life"],
            this->parser._parsedData["Health"]["maxHealth"]
        );
        entity->createComponent<Weapon>(
            "Bullet",
            this->parser._parsedData["Weapon"]["damage"],
            this->parser._parsedData["Weapon"]["ammo"]
        );
    } else if (name == "BossBullet") {
        this->parser.GetJsonInfos("BossBullet", this->parser._parsedData);
        entity->createComponent<TypeEntity>(bossBullet);
        entity->createComponent<Input>(0, 0, false, true);
        entity->createComponent<Position>(
            this->parser._parsedData["Position"]["x"],
            this->parser._parsedData["Position"]["y"],
            this->parser._parsedData["Position"]["z"],
            this->parser._parsedData["Position"]["speed"]
        );
        entity->createComponent<Collider>(
            this->parser._parsedData["Collider"]["width"],
            this->parser._parsedData["Collider"]["height"],
            this->parser._parsedData["Collider"]["layer"]
        );
        entity->createComponent<Health>(
            this->parser._parsedData["Health"]["life"],
            this->parser._parsedData["Health"]["maxHealth"]
        );
        entity->createComponent<Weapon>(
            "BossBullet",
            this->parser._parsedData["Weapon"]["damage"],
            this->parser._parsedData["Weapon"]["ammo"]
        );
    } else if (name == "Rocket") {
        this->parser.GetJsonInfos("Rocket", this->parser._parsedData);
        entity->createComponent<TypeEntity>(rocket);
        entity->createComponent<Input>(0, 0, false, true);
        entity->createComponent<Position>(
            this->parser._parsedData["Position"]["x"],
            this->parser._parsedData["Position"]["y"],
            this->parser._parsedData["Position"]["z"],
            this->parser._parsedData["Position"]["speed"]
        );
        entity->createComponent<Collider>(
            this->parser._parsedData["Collider"]["width"],
            this->parser._parsedData["Collider"]["height"],
            this->parser._parsedData["Collider"]["layer"]
        );
        entity->createComponent<Health>(
            this->parser._parsedData["Health"]["life"],
            this->parser._parsedData["Health"]["maxHealth"]
        );
        entity->createComponent<Weapon>(
            "Rocket",
            this->parser._parsedData["Weapon"]["damage"],
            this->parser._parsedData["Weapon"]["ammo"]
        );

    } else if (name == "PowerUpHealth") {
        entity->createComponent<TypeEntity>(PowerUpHealth);
        entity->createComponent<Position>(600, 100, 0, 1);
        entity->createComponent<Collider>(32, 32, 2);
        entity->createComponent<Health>(1, 1);
        entity->createComponent<Input>(-1, 0, false, true);
        entity->createComponent<Powerup>(HEALTH, 10);
    } else if (name == "PowerUpSpeed") {
        entity->createComponent<TypeEntity>(PowerUpSpeed);
        entity->createComponent<Position>(600, 100, 0, 1);
        entity->createComponent<Collider>(32, 32, 2);
        entity->createComponent<Health>(1, 1);
        entity->createComponent<Input>(-1, 0, false, true);
        entity->createComponent<Powerup>(SPEED, 10);
    } else if (name == "PowerUpDamage") {
        entity->createComponent<TypeEntity>(PowerUpDamage);
        entity->createComponent<Position>(600, 100, 0, 1);
        entity->createComponent<Collider>(32, 32, 2);
        entity->createComponent<Health>(1, 1);
        entity->createComponent<Input>(-1, 0, false, true);
        entity->createComponent<Powerup>(DAMAGE, 10);
    } else if (name == "PowerUpDoubleShoot") {
        entity->createComponent<TypeEntity>(PowerUpDoubleShoot);
        entity->createComponent<Position>(600, 100, 0, 1);
        entity->createComponent<Collider>(32, 32, 2);
        entity->createComponent<Health>(1, 1);
        entity->createComponent<Input>(-1, 0, false, true);
        entity->createComponent<Powerup>(DOUBLESHOOT, 1);
    } else if (name == "PowerUpRocketShoot") {
        entity->createComponent<TypeEntity>(PowerUpRocketShoot);
        entity->createComponent<Position>(600, 100, 0, 1);
        entity->createComponent<Collider>(32, 32, 2);
        entity->createComponent<Health>(1, 1);
        entity->createComponent<Input>(-1, 0, false, true);
        entity->createComponent<Powerup>(ROCKETSOOT, 10);
     } else {
        std::cout << "Entity " << name << " not found" << std::endl;
    }

    return *entity;
}

#if defined(_WIN32) || defined(_WIN64)
    #pragma warning(default: 4244)
#endif
