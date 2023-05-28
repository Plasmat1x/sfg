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

struct ImageLayer {
    float opacity;
    sf::Color tintcolor;
    float offestx;
    float offsety;
    float parallaxx;
    float parallaxy;
    bool repeatx;
    bool repeaty;
    int width;
    int height;
    sf::Texture texture;
};