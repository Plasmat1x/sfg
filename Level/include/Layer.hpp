#pragma once
#include<SFML/Graphics.hpp>

struct TileLayer {
    float opacity;
    sf::Color tintcolor;
    float offestx;
    float offsety;
    float parallaxx;
    float parallaxy;
    std::vector<sf::Sprite> tiles;
};