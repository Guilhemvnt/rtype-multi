/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** InputButton
*/

#ifndef INPUTBUTTON_HPP_
#define INPUTBUTTON_HPP_
#include "Button.hpp"

class InputButton : public Button{
    public:
    InputButton(sf::RectangleShape rectShape, sf::Vector2f pos, sf::Text text, sf::Color defaultColor)
        : Button(rectShape, pos, text, defaultColor), keyRepeatDelay(sf::milliseconds(80)) {}
        void handleInputs(sf::Event event);
        sf::String clientInput;
    protected:
        sf::Clock keyRepeatClock;
        sf::Time keyRepeatDelay;
    private:
};

#endif /* !INPUTBUTTON_HPP_ */
