/*
** EPITECH PROJECT, 2023
** File description:
** Button
*/

#ifndef BUTTON_HPP_
    #define BUTTON_HPP_
    #include <SFML/Graphics.hpp>
    #include <iostream>
    #include <JsonParser/JsonParser.hpp>

    class Button {
        public:
            JsonParser parser;

            sf::Color _defaultColor;
            sf::Color _hoverColor;

            sf::RectangleShape _RectShape;
            sf::Text _text;
            sf::Font _font;
            sf::Vector2f _pos;

            bool isHover = false;
            bool active = true;

            Button(sf::RectangleShape, sf::Vector2f, sf::Text, sf::Color);
            ~Button();
            void draw(sf::RenderWindow &);
            bool isClicked(const sf::Vector2f& mousePos, const sf::Event&, const sf::RenderWindow& window);

            Button &operator=(const Button &other) {
                _RectShape = other._RectShape;
                _text = other._text;
                _font = other._font;
                isHover = other.isHover;
                return *this;
            };
    };

#endif /* !BUTTON_HPP_ */
