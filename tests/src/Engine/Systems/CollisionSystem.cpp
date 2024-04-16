/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** CollisionSystem
*/

#include <Engine/Systems/CollisionSystem.hpp>

CollisionSystem::CollisionSystem() { }

CollisionSystem::~CollisionSystem() { }


bool CollisionSystem::isCollision(std::shared_ptr<Entity>  entity1, std::shared_ptr<Entity>  entity2, int entityID1, int entityID2) {
    if (entity2->hasComponent<Collider>() && entityID1 != entityID2 &&
        entity1->getComponent<Collider>().layer != entity2->getComponent<Collider>().layer) {

        if (entity1->hasComponent<Powerup>() && entity2->getComponent<TypeEntity>().t != player) {
            return false;
        }
        if (entity2->hasComponent<Powerup>() && entity1->getComponent<TypeEntity>().t != player) {
            return false;
        }
        auto& pos1 = entity1->getComponent<Position>();
        auto& col1 = entity1->getComponent<Collider>();

        auto& pos2 = entity2->getComponent<Position>();
        auto& col2 = entity2->getComponent<Collider>();

        return (pos1.x < pos2.x + col2.width && pos1.x + col1.width > pos2.x &&
                pos1.y < pos2.y + col2.height && pos1.y + col1.height > pos2.y);
    }

    return false;
}

void CollisionSystem::setPowerUp(std::shared_ptr<Entity>  entity1, std::shared_ptr<Entity> entity2) {
    auto& health = entity1->getComponent<Health>();
    if (entity2->hasComponent<Powerup>() && entity1->getComponent<TypeEntity>().t == player) {
        auto& powerup = entity2->getComponent<Powerup>();
        if (powerup.t == HEALTH) {
            health.health += powerup.value;
            if (health.health >= health.maxHealth)
                health.health = health.maxHealth;
        }
        if (powerup.t == SPEED) {
            entity1->getComponent<Position>().speed = 10;
        }
        if (powerup.t == DAMAGE) {
            entity1->getComponent<Weapon>().damage += powerup.value;
        }
        if (powerup.t == DOUBLESHOOT) {
            entity1->getComponent<Weapon>().maxAmmo = 2;
        }
        if (powerup.t == ROCKETSOOT) {
            entity1->getComponent<Weapon>().ammoRocket += 1;
        }
        entity2->getComponent<Health>().health = 0;
    }
}

bool CollisionSystem::isDead(std::shared_ptr<Entity>  entity1, std::shared_ptr<Entity> entity2) {
    entity1->getComponent<Collider>().colliding = true;
    entity2->getComponent<Collider>().colliding = true;
    auto& health = entity1->getComponent<Health>();

    if (entity2->hasComponent<Weapon>() && !entity1->hasComponent<Powerup>()) {
        health.health -= entity2->getComponent<Weapon>().damage;
    }

    setPowerUp(entity1, entity2);

    if (health.health <= 0) {
        entity1->getComponent<Collider>().colliding = false;
        entity2->getComponent<Collider>().colliding = false;
        return true;
    }

    return false;
}

void CollisionSystem::update(std::shared_ptr<EntityManager>& entityManager, float deltaTime)
{
    auto entities = entityManager->getEntities();

    for (auto& [entityID1, entity1] : entities) {
        if (entity1->hasComponent<Collider>()) {
            for (auto& [entityID2, entity2] : entities) {
                if (isCollision(entity1, entity2, entityID1, entityID2)) {
                    if (isDead(entity1, entity2)) {
                        entityManager->entitiesToDestroy.push_back(entity1);
                    } else {
                        entityManager->entitiesDamaged.push_back(entity1);
                    }
                } else {
                    entity1->getComponent<Collider>().colliding = false;
                }
            }
        }
    }
}
