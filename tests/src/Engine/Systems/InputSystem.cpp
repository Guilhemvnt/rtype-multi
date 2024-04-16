/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** InputSystem
*/

#include "Engine/Systems/InputSystem.hpp"

InputSystem::InputSystem() { _entityFactory = EntityFactory(); }

InputSystem::~InputSystem() { }

void InputSystem::update(std::shared_ptr<EntityManager>& entityManager, float deltaTime)
{
    for (auto& [_, entity] : entityManager->getEntities()) {
        if (entity->hasComponent<Input>() == true && entity->hasComponent<Weapon>() == true) {
            if (entity->getComponent<Input>().shoot == true) {
                while (entity->getComponent<Weapon>().ammo > 0) {
                    Entity bullet;
                    if (entity->getComponent<TypeEntity>().t == boss)
                        bullet = _entityFactory.createEntity("BossBullet");
                    else
                        bullet = _entityFactory.createEntity("Bullet" + std::to_string(entity->getComponent<Weapon>().shootLevel));
                    bullet.getComponent<Collider>().layer = entity->getComponent<Collider>().layer;
                    bullet.getComponent<Position>().x = entity->getComponent<Position>().x;
                    bullet.getComponent<Position>().y = entity->getComponent<Position>().y + ((entity->getComponent<Weapon>().ammo - 1) * 40);
                    if (entity->getComponent<TypeEntity>().t == player)
                        bullet.getComponent<Position>().speed = 2 * entity->getComponent<Position>().speed;
                    bullet.getComponent<Weapon>().damage =  entity->getComponent<Weapon>().damage;

                    if (entity->getComponent<TypeEntity>().t == boss)
                        bullet.getComponent<Input>().x = -1;
                    else
                        bullet.getComponent<Input>().x = entity->getComponent<Input>().x;

                    if (bullet.getComponent<Input>().x == 0)
                        bullet.getComponent<Input>().x = 1;
                    entityManager->createEntity(bullet);
                    entity->getComponent<Weapon>().ammo--;
                }
                entity->getComponent<Input>().shoot = false;
                if (entity->getComponent<TypeEntity>().t == enemy || entity->getComponent<TypeEntity>().t == boss)
                    auto y = entity->getComponent<Input>().y = (rand() % 2) * 2 - 1;
            } else if (entity->getComponent<Input>().shoot == false && (entity->getComponent<TypeEntity>().t == enemy || entity->getComponent<TypeEntity>().t == boss)) {
                sf::Time elapsedTime = timer.getElapsedTime();
                if (elapsedTime >= resetTimer) {
                    entity->getComponent<Input>().shoot = true;
                    entity->getComponent<Weapon>().ammo = entity->getComponent<Weapon>().maxAmmo;
                    timer.restart();
                }
            }

            if (entity->getComponent<Input>().rocketShoot == true && entity->getComponent<Weapon>().ammoRocket > 0) {
                Entity bullet = _entityFactory.createEntity("Rocket");
                bullet.getComponent<Collider>().layer = entity->getComponent<Collider>().layer;
                bullet.getComponent<Position>().x = entity->getComponent<Position>().x;
                bullet.getComponent<Position>().y = entity->getComponent<Position>().y + 10;
                bullet.getComponent<Weapon>().damage =  entity->getComponent<Weapon>().damage;

                bullet.getComponent<Input>().x = 1;

                entityManager->createEntity(bullet);

                entity->getComponent<Weapon>().ammoRocket--;
                entity->getComponent<Input>().rocketShoot = false;
            }
        }
    }


}
