/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** Health
*/

#ifndef HEALTH_HPP_
#define HEALTH_HPP_
#include "Engine/Components/IComponent.hpp"

class Health : public IComponent {
public:
    int health;
    int maxHealth;

    Health(int health, int maxHealth)
        : health(health)
        , maxHealth(maxHealth) {};
    ~Health() = default;
};
inline std::ostream& operator<<(std::ostream& out, const Health* health)
{
    out << "Health: " << health->health << ", " << health->maxHealth << std::endl;
    return out;
}

#endif /* !HEALTH_HPP_ */
