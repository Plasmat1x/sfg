#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>

#include <SFML/Graphics.hpp>

#include <tinyxml2.h>

using namespace tinyxml2;

struct Point {
    float x;
    float y;
};

std::vector<int> parseCSV(std::string str);
sf::Color hexToColor(const char* hexstring);
std::vector<Point> parsePoints(std::string string);

class Level;

class MapParser
{
public:
    MapParser();
    MapParser(std::string FILE, Level* level);
    ~MapParser();

    void init(std::string FILE);
    void cleanup();
private:
    Level* level;
    std::string PATH = "../resources/maps/";

    int firstTileID;

    sf::Vector2f tileSize;
    sf::Vector2f mapTiles;
    sf::Vector2i tilesetArray;

    std::vector<sf::IntRect> subRects;

    XMLDocument document;

    void parseTileset(std::string FILE);
    void parseGroups(XMLElement* root);
    void parseObjects(XMLElement* root);
    void parseImages(XMLElement* root);
    void parseTiles(XMLElement* root);

    friend class Level;
};