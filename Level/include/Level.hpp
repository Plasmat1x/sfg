#pragma once

#include<vector>
#include<string>
#include<iostream>
#include<stdlib.h>
#include<sstream>

#include<SFML/Graphics.hpp>

#include<tinyxml2.h>

#include"Layer.hpp"
#include"Background.hpp"
#include"InfScroller.hpp"

class MapParser;

using namespace tinyxml2;

class Level : public sf::Drawable {
public:
    Level();
    Level(std::string FILE, sf::View* view);
    ~Level();

    void init(std::string FILE, sf::View* view);
    void cleanup();
    void setView(sf::View* view);

    void update();
    virtual void draw(sf::RenderTarget& tg, sf::RenderStates state) const;

private:
    sf::View* view;
    sf::Texture* texture;

    std::vector<TileLayer> layers;
    //FIXME: when use direct pushback bgs errors;
    std::vector<InfScroller*> backgrounds;

    friend class MapParser;
};




