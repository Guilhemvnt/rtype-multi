/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** Type
*/

#ifndef TYPE_HPP_
#define TYPE_HPP_
    #include "IComponent.hpp"

    enum type {
        defaultType,
        player,
        enemy,
        block,
        bullet0,
        bullet1,
        bullet2,
        bullet3,
        bullet4,
        bullet,
        boss,
        bossBullet,
        rocket,
        PowerUpHealth,
        PowerUpSpeed,
        PowerUpDamage,
        PowerUpDoubleShoot,
        PowerUpRocketShoot
    };

    class TypeEntity : virtual public IComponent {
        public:
            TypeEntity(type t) : t(t) {};
            type t;
    };

#endif /* !TYPE_HPP_ */
