#pragma once

#include <SFML/Graphics.hpp>

namespace u
{
    bool Intersect(sf::Vector2f point, sf::FloatRect target);
    bool Intersect(sf::Vector2i point, sf::RectangleShape target);
    bool Intersect(sf::RectangleShape cur, sf::RectangleShape target);
}
