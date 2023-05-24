#pragma once

#include<vector>
#include<string>
#include<iostream>
#include<tinyxml2.h>
#include<stdlib.h>
#include<sstream>
#include<SFML/Graphics.hpp>

using namespace tinyxml2;

struct Layer {
    int opacity;
    sf::Color tintcolor;
    std::vector<sf::Sprite> tiles;
};

class Level : public sf::Drawable {
public:
    Level() {
        texture = nullptr;
    }
    Level(const char* FILE) {
        init(FILE);
    }
    ~Level() {
        if (texture) {
            delete texture;
        }
    }

    void init(const char* FILE) {
        document.LoadFile(FILE);

        std::string data = document.FirstChildElement("map")->FirstChildElement("layer")->FirstChildElement("data")->GetText();
        std::vector<int> ids = parseCSV(data);
        /*
        for (int i : ids) {
            printf("%d ", i);
        }
        */
        initSubRects(document.FirstChildElement("map")->FirstChildElement("tileset")->Attribute("source"));
    }

    virtual void draw(sf::RenderTarget& tg, sf::RenderStates state) const {
        for (Layer L : layers) {
            for (sf::Sprite T : L.tiles) {
                tg.draw(T);
            }
        }
    }

    void test(const char* s) {
        hexToVec3(s);
    }

private:
    tinyxml2::XMLDocument document;

    int firstTileID;

    sf::Vector2f tileSize;
    sf::Vector2f mapTiles;
    sf::Vector2i tilesetArray;
    sf::Rect<float> drawingBound;
    sf::Texture* texture;
    sf::Vector3f mapPosition;
    std::vector<Layer> layers;
    std::vector<sf::Rect<int>> subRects;

    std::vector<int> parseCSV(std::string string) {
        std::vector<int> vect;

        std::stringstream ss(string);

        for (int i; ss >> i;) {
            vect.push_back(i);
            if (ss.peek() == ',')
                ss.ignore();
        }

        return vect;
    }

    void initSubRects(const char* FILE) {
        XMLDocument* doc = nullptr;
        doc->LoadFile(FILE);
        texture = new sf::Texture;
        XMLElement* e = doc->FirstChildElement("tileset");

        int N = atoi(e->Attribute("columns"));
        int S = atoi(e->Attribute("tilecount"));
        int M = S / N;

        int margin = 0;
        int spacing = 0;

        if (e->Attribute("margin")) margin = atoi(e->Attribute("margin"));
        if (e->Attribute("spacing")) spacing = atoi(e->Attribute("spacing"));

        int tilewidth = atoi(e->Attribute("tilewidth"));
        int tileheight = atoi(e->Attribute("tileheight"));

        for (int y = 0; y < M; y++) {
            for (int x = 0; x < N; y++) {
                sf::Rect<int> rect;

                rect.left = margin + (spacing + tilewidth) * x;
                rect.top = margin + (spacing + tileheight) * y;
                rect.width = tilewidth;
                rect.height = tileheight;

                subRects.push_back(rect);
            }
        }

        e = doc->FirstChildElement("tileset")->FirstChildElement("image");
        texture->loadFromFile(e->Attribute("source"));

    }

    sf::Color hexToVec3(const char* hexstring) {
        uint32_t hexdec;
        std::stringstream ss(hexstring);
        if (ss.peek() == '#') ss.ignore();
        ss >> std::hex >> hexdec;

        unsigned int r, g, b, a;
        unsigned int bitmask = 255;

        if (((hexdec >> 24) & bitmask) > 0) {

            b = (hexdec >> 0) & bitmask;
            g = (hexdec >> 8) & bitmask;
            r = (hexdec >> 16) & bitmask;
            a = (hexdec >> 24) & bitmask;
        }
        else {
            b = (hexdec & bitmask);
            g = (hexdec >> 8) & bitmask;
            r = (hexdec >> 16) & bitmask;
            a = 255;
        }

        printf("r = %d\ng = %d\nb = %d\na = %d\n", r, g, b, a);

        return sf::Color(r, g, b, a);
    }
};//class Level

/*//target usage
    Level l;
    l.init("../resources/maps/map2.tmx");

    //class worked version
    void init(const char* FILE) {
        document.LoadFile(FILE);

        std::string data = document.FirstChildElement("map")->FirstChildElement("layer")->FirstChildElement("data")->GetText();
        std::vector<int> ids = parseCSV(data);

        for (int i : ids) {
            printf("%d ", i);
        }
    }*/



