/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** Engine
*/

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include <Engine/Entities/EntityManager.hpp>
#include <Engine/Systems/AISystem.hpp>
#include <Engine/Systems/CollisionSystem.hpp>
#include <Engine/Systems/InputSystem.hpp>
#include <Engine/Systems/MvtSystem.hpp>
#include <Engine/Systems/PowerupSystem.hpp>

#include <Engine/Components/Collider.hpp>
#include <Engine/Components/Health.hpp>
#include <Engine/Components/Input.hpp>
#include <Engine/Components/Position.hpp>
#include <Engine/Components/Weapon.hpp>

#include <Engine/Entities/EntityFactory.hpp>

class Engine {
    private:
        JsonParser parser;
        std::vector<std::shared_ptr<ISystem>> _systems;
    public:
        std::shared_ptr<AISystem> _systemAI;
        EntityFactory _entityFactory;
        std::shared_ptr<EntityManager> gameObjects;
        EcsGameType _launchedGameType;

        Engine();
        ~Engine();
        int addPlayer();
        void update(float deltaTime);
        void clean();
        void start(EcsGameType);
        std::string restart(bool &,  int &);
};

#endif /* !ENGINE_HPP_ */
