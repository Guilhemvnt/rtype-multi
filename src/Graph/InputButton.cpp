/*
** EPITECH PROJECT, 2024
** B-CPP-500-LYN-5-2-rtype-erwann.laplante
** File description:
** InputButton
*/

#include <Graph/InputButton.hpp>

void InputButton::handleInputs(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed) {
        keyRepeatClock.restart();
    } else if (event.type == sf::Event::TextEntered) {
        if (((event.text.unicode >= '0' && event.text.unicode <= '9') || event.text.unicode == '.') && clientInput.getSize() < 15) {
            if (keyRepeatClock.getElapsedTime() > keyRepeatDelay) {
                clientInput += static_cast<char>(event.text.unicode);
                _text.setString(clientInput);
                _text.setPosition(_text.getPosition().x - 7, _text.getPosition().y);
                keyRepeatClock.restart();
            }
        } else if (event.text.unicode == 8 && !clientInput.isEmpty()) {
            if (keyRepeatClock.getElapsedTime() > keyRepeatDelay) {
                clientInput.erase(clientInput.getSize() - 1);
                _text.setString(clientInput);
                _text.setPosition(_text.getPosition().x + 7, _text.getPosition().y);
                keyRepeatClock.restart();
            }
        }
    }
}
