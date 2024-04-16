/*
** EPITECH PROJECT, 2023
** File description:
** Button
*/

#include <Graph/Button.hpp>

Button::Button(sf::RectangleShape rect, sf::Vector2f pos, sf::Text txt, sf::Color defaultColor)
: parser("src/Graph/GameConfig.json")
{
    _defaultColor = defaultColor;
    _hoverColor = sf::Color(0, 0, 0);

    _RectShape = rect;
    _RectShape.setFillColor(_defaultColor);
    _RectShape.setPosition(pos);
    _RectShape.setOutlineThickness(2);
    _pos = pos;

    _text = txt;

    sf::Vector2f rectCenter = pos + 0.5f * sf::Vector2f(_RectShape.getSize());
    sf::FloatRect textBounds = _text.getLocalBounds();
    sf::Vector2f textCenter(rectCenter.x - 0.5f * textBounds.width, rectCenter.y - 0.5f * textBounds.height);

    _text.setPosition(textCenter);

    this->parser.GetJsonInfos("Color", this->parser._parsedData);

    _text.setFillColor(sf::Color(this->parser._parsedData["ButtonText"]["red"],
        this->parser._parsedData["ButtonText"]["green"],
        this->parser._parsedData["ButtonText"]["blue"]));
}

Button::~Button()
{
}

bool Button::isClicked(const sf::Vector2f& mousePos, const sf::Event& event, const sf::RenderWindow& window)
{
    sf::Vector2f windowMousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

    if (_RectShape.getGlobalBounds().contains(windowMousePos) && active) {
        _RectShape.setFillColor(_hoverColor);
        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
            return true;
    }

    _RectShape.setFillColor(_defaultColor);
    return false;
}

void Button::draw(sf::RenderWindow &window)
{
    if (active) {
        window.draw(_RectShape);
        window.draw(_text);
    }
}