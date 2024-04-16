/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** PowerupSystem
*/

#ifndef POWERUPSYSTEM_HPP_
    #define POWERUPSYSTEM_HPP_
    #include <Engine/Systems/ISystem.hpp>
    class PowerupSystem : public virtual ISystem{
        public:
            PowerupSystem();
            ~PowerupSystem();

            void update(std::shared_ptr<EntityManager>&, float deltaTime);

        protected:
            sf::Clock timer;
            sf::Time timerBetweenPowerup = sf::seconds(5.0f);
        private:
    };

#endif /* !POWERUPSYSTEM_HPP_ */
