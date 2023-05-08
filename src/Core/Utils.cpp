#include "Core/Utils.hpp"

/*
    sf::Vector2f -> const sf::Vector2f&
*/

namespace u
{
    bool Intersect(sf::Vector2f point, sf::FloatRect target)
    {
        if (point.x >= target.left &&
            point.x <= target.left + target.width &&
            point.y >= target.top &&
            point.y <= target.top + target.height)
            return true;

        return false;
    }

    bool Intersect(sf::Vector2i point, sf::RectangleShape target)
    {
        if (point.x >= target.getPosition().x &&
            point.x <= target.getPosition().x + target.getSize().x &&
            point.y >= target.getPosition().y &&
            point.y <= target.getPosition().y + target.getSize().y)
            return true;

        return false;
    }

    bool Intersect(sf::RectangleShape cur, sf::RectangleShape target)
    {
        bool intersect_x = false;
        bool intersect_y = false;

        if ((cur.getPosition().x >= target.getPosition().x &&
             cur.getPosition().x <= target.getPosition().x + target.getSize().x) ||
            (cur.getPosition().x + cur.getSize().x >= target.getPosition().x &&
             cur.getPosition().x + cur.getSize().x <= target.getPosition().x + target.getSize().x))
            intersect_x = true;

        if ((cur.getPosition().y >= target.getPosition().y &&
             cur.getPosition().y <= target.getPosition().y + target.getSize().y) ||
            (cur.getPosition().y + cur.getSize().y >= target.getPosition().y &&
             cur.getPosition().y + cur.getSize().y <= target.getPosition().y + target.getSize().y))
            intersect_y = true;

        return intersect_x && intersect_y;
    }
}
