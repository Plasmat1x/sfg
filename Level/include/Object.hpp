#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

class Object : public sf::Drawable {
private:
    sf::Vector2f position;
    sf::Vector2f size;
public:
    Object() {};
    ~Object() {};

    void draw(sf::RenderTarget& tg, sf::RenderStates st) const {

    }
};