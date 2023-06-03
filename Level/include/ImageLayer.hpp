#pragma once

#include "Layer.hpp"

class ImageLayer : public Layer {
private:
    std::string image;
    sf::Color trans;
    bool repeatx;
    bool repeaty;
public:
    ImageLayer();
    ~ImageLayer();
};