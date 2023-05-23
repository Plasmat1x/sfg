#pragma once

#include<vector>
#include<string>
#include<tinyxml2.h>
#include<stdlib.h>

using namespace tinyxml2;

struct ImageInfo {
    const char* source;
    int width;
    int height;
}

struct TileSetInfo {
    int tilewidth;
    int tileheight;
    int tilecount;
    int columns;
}

struct MapInfo {
    int width;
    int height;
    int tilewidth;
    int tileheight;
}

struct LayerInfo {
    int id;
    int width;
    int height;
    float opacity;
    uint32_t tintcolor;
}

struct LayerCSV {
    const char* data;
}

struct Object {
    int id;
    const char* name;
    int x;
    int y;
    int width;
    int height;
}

struct Tile {
    int x;
    int y;
    int w;
    int h;
    int tx;
    int ty;
    int tw;
    int th;
}

//TODO: csv/string parse
/*
tinyxml2::XMLDocument document;
document.LoadFile("../resources/Maps/map2.tmx");
std::string data = document.FirstChildElement("map")->FirstChildElement("layer")->FirstChildElement("data")->GetText();
printf(data.c_str());
*/

std::vector<int> parseCVS(std::string string) {
    int i, y = 0;
    std::vector<int> res;
}

class Level {
public:
    void init(const char* FILE) {

    }

private:
    std::vector<Tile> tiles;
    std::vector<Object> objects;

}