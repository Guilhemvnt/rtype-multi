/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** PowerupSystem
*/

#include <Engine/Systems/PowerupSystem.hpp>

PowerupSystem::PowerupSystem()
{
}

PowerupSystem::~PowerupSystem()
{
}

void PowerupSystem::update(std::shared_ptr<EntityManager>& entityManager, float deltaTime)
{
    std::vector<std::string> es = {"PowerUpRocketShoot", "PowerUpDoubleShoot", "PowerUpDamage", "PowerUpHealth", "PowerUpSpeed"};
    sf::Time elapsedTime = timer.getElapsedTime();
    int i = 0;
    if (elapsedTime > timerBetweenPowerup) {
        Entity e =  EntityFactory().createEntity(es[rand() % es.size()]);
        auto r = (rand() % 10);
        e.getComponent<Position>().y = 60 * r;
        entityManager->createEntity(e);

        timer.restart();
    }
}
