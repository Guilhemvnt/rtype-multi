/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** Weapon
*/

#ifndef WEAPON_HPP_
#define WEAPON_HPP_
#include <Engine/Components/IComponent.hpp>
#include <vector>

class Weapon : public IComponent {
public:
    std::string name;
    int damage;
    int shootLevel = 0;
    int ammo = 0;
    int maxAmmo = 0;
    int ammoRocket = 0;

    Weapon(std::string name, int damage, float ammo)
        : name(name)
        , damage(damage)
        , ammo(ammo)
        , maxAmmo(ammo) {};
    ~Weapon() = default;
};
inline std::ostream& operator<<(std::ostream& out, const Weapon* weapon)
{
    out << "Weapon: " << weapon->name << ", " << weapon->damage << ", "
        << weapon->ammo << ", " << weapon->maxAmmo << std::endl;
    return out;
}

#endif /* !WEAPON_HPP_ */
