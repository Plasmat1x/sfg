#pragma once
#include<SFML/Graphics.hpp>

class Layer {
private:
    unsigned int _id;
    std::string _name;
    std::string _class;
    bool _visible;
    bool _locked;
    float _opacity;
    sf::Color _tintcolor;
    float _offsetx;
    float _offsety;
    float _parallaxx;
    float _parallaxy;
public:
    virtual ~Layer();
};

struct TileLayer {
    float opacity;
    sf::Color tintcolor;
    float offsetx;
    float offsety;
    float parallaxx;
    float parallaxy;
    std::vector<sf::Sprite> tiles;
};