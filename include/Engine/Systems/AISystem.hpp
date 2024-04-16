/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** AISystem
*/

#ifndef AISYSTEM_HPP_
#define AISYSTEM_HPP_

#include <Engine/EcsGameType.hpp>
#include <JsonParser/JsonParser.hpp>
#include <Engine/Systems/ISystem.hpp>

class AISystem : virtual public ISystem {
    public:
        AISystem(EcsGameType);
        ~AISystem();

        void update(std::shared_ptr<EntityManager>&, float deltaTime);

        int nbAI = 0;
        int maxAI;
        bool bossIsSpawned = false;
        bool bossIsDead = false;
        int nbAidead = 0;
        EcsGameType _gameType;

    private:
        void updateGameValues();
        void createAI(std::shared_ptr<EntityManager>& entityManager);

    protected:
        JsonParser parser;
        sf::Clock timer;
        sf::Time timerBetweenAI;
        sf::Time timerBetweenWaves;
        sf::Time waitTimer = timerBetweenAI;
        sf::Time changeDirectionTimer = sf::seconds(2.0f);
};

#endif /* !AISYSTEM_HPP_ */
