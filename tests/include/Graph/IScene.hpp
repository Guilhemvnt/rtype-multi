/*
** EPITECH PROJECT, 2023
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** IScene
*/

#ifndef ISCENE_HPP_
#define ISCENE_HPP_

#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Network.hpp>

#include <map>

class IScene {
public:
    IScene() = default;
    ~IScene() = default;
    virtual void run() = 0;

protected:
private:
};

#endif /* !ISCENE_HPP_ */
