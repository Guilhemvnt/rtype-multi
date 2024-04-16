/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** GameObject
*/

#include <Graph/GameObject.hpp>

void GameObject::render(sf::RenderWindow& window)
{
    window.draw(this->sprite);
    window.draw(this->backgroundHealthBar);
    window.draw(this->backgroundPowerBar);
    window.draw(this->healthBar);
    window.draw(this->powerBar);
}

void GameObject::animate(sf::Time deltaTime)
{
    int spriteWidth = this->sprite.getTextureRect().width;
    int spriteHeight = this->sprite.getTextureRect().height;
    int rectLeftPos = this->sprite.getTextureRect().left;
    int rectTopPos = this->sprite.getTextureRect().top;

    if (this->animationTimer.getElapsedTime() > deltaTime) {
        if (spriteWidth != 0 && spriteHeight != 0 && nbFrames != 0) {
            this->animationTimer.restart();
            this->sprite.setTextureRect(sf::IntRect(this->animationFrame * spriteWidth, rectTopPos, spriteWidth, spriteHeight));
            this->animationFrame++;

            if (this->animationFrame > nbFrames)
                this->animationFrame = 0;
        }
    }
}

