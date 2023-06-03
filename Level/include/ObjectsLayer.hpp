#pragma once

#include "Layer.hpp"

class ObjectsLayer : public Layer {
private:
    sf::Color color;
public:
    ObjectsLayer();
    ~ObjectsLayer();
};