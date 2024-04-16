/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** GameObject
*/

#ifndef GAMEOBJECT_HPP_
    #define GAMEOBJECT_HPP_
    #include <SFML/Audio.hpp>
    #include <SFML/Graphics.hpp>
    #include <SFML/Window.hpp>
    #include <SFML/Window/Keyboard.hpp>
    #include <iostream>
    #include <memory>
    #include <vector>

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

    class GameObject {
        public:
            GameObject() = default;
            ~GameObject() = default;
            void render(sf::RenderWindow&);
            void animate(sf::Time deltaTime);

            int id;
            int speed;
            int health;
            int power;
            enum type type;

            int nbFrames = 0;
            sf::Clock animationTimer;
            int animationFrame = 0;
            sf::Vector2f velocity;
            sf::Sprite sprite;
            sf::Texture texture;

            sf::RectangleShape healthBar;
            sf::RectangleShape backgroundHealthBar;
            sf::RectangleShape powerBar;
            sf::RectangleShape backgroundPowerBar;
    };
#endif /* !GAMEOBJECT_HPP_ */
