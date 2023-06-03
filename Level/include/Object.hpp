#pragma once
#include <string>

class Object {
private:
    unsigned int _id;
    std::string _name;
    std::string _class;
    bool visible;
    float x;
    float y;
    float rotation;
public:
}

class RectangleObject;
class TileObject;
class PointObject;
class ElipseObject;
class PolygonObject;