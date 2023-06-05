#pragma once
#include<SFML/Graphics.hpp>
#include"Object.hpp"

struct ObjectsLayer {
    bool visible = true;
    float opacity = 1.0f;
    sf::Color tintcolor = sf::Color(255, 255, 255, 255);
    float offsetx = 0.0f;
    float offsety = 0.0f;
    float parallaxx = 1.0f;
    float parallaxy = 1.0f;
    sf::Color color = sf::Color(255, 255, 255, 255);
    std::vector<sf::ConvexShape> shapes;
    std::vector<Object> objects;
};

struct TileLayer {
    float opacity = 1.0f;
    sf::Color tintcolor = sf::Color(255, 255, 255, 255);
    float offsetx = 0.0f;
    float offsety = 0.0f;
    float parallaxx = 1.0f;
    float parallaxy = 1.0f;
    std::vector<sf::Sprite> tiles;
};