#pragma once

#include "Layer.hpp"

class GroupLayer : public Layer {
private:
    std::vector<Layer*> childs;
public:
    GroupLayer();
    ~GroupLayer();
};