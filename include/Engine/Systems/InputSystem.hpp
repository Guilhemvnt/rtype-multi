/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** InputSystem
*/

#ifndef INPUTSYSTEM_HPP_
#define INPUTSYSTEM_HPP_
#include <Engine/Systems/ISystem.hpp>

class InputSystem : virtual public ISystem {
public:
    InputSystem();
    ~InputSystem();

    void update(std::shared_ptr<EntityManager>&, float deltaTime);

protected:
    EntityFactory _entityFactory;

    sf::Clock timer;
    sf::Time resetTimer = sf::seconds(2.0f);

private:
};

#endif /* !INPUTSYSTEM_HPP_ */
