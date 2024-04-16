/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** Input
*/

#ifndef INPUT_HPP_
#define INPUT_HPP_
#include "Engine/Components/IComponent.hpp"
#include "Engine/Entities/EntityFactory.hpp"

class Input : public IComponent {
public:
    int x = 0;
    int y = 0;

    bool shoot = false;
    bool isUpdated = false;
    bool rocketShoot = false;
    int yDirection = 1;

    Input() {};
    Input(int x, int y, bool shoot, bool isUpdated)
        : x(x)
        , y(y)
        , shoot(shoot)
        , isUpdated(isUpdated) {};
    ~Input() {};


protected:
private:
};

#endif /* !INPUT_HPP_ */
