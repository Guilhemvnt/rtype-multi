/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** MvtSystem
*/

#include "Engine/Systems/MvtSystem.hpp"

MvtSystem::MvtSystem() { }

MvtSystem::~MvtSystem() { }

void MvtSystem::update(std::shared_ptr<EntityManager>& entityManager, float deltaTime)
{
    for (auto& [_, entity] : entityManager->getEntities()) {
        if (entity->hasComponent<Input>() && !entity->getComponent<Collider>().colliding && entity->getComponent<Input>().isUpdated) {
            auto& position = entity->getComponent<Position>();
            auto& input = entity->getComponent<Input>();
            auto& collider = entity->getComponent<Collider>();

            position.x += input.x * position.speed;
            position.y += input.y * position.speed;

            if (position.y < 0)
                position.y = 600;
            if (position.y > 600)
                position.y = 0;

            if (position.x < 0 - collider.width || position.x > 800 + collider.width) {
                entity->deathReason = EntityDeathReason::Suicided;
                entityManager->entitiesToDestroy.push_back(entity);
            }
        }
    }
}

