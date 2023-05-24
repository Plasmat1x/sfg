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
    float opacity;
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

    void init(std::string FILE) {
        XMLDocument doc;
        std::string PF = PATH + FILE;
        doc.LoadFile(PF.c_str());
        PF = PATH + doc.FirstChildElement("map")->FirstChildElement("tileset")->Attribute("source");
        initSubRects(PF.c_str());

        firstTileID = doc.FirstChildElement("map")->FirstChildElement("tileset")->IntAttribute("firstgid");

        XMLElement* element = doc.FirstChildElement("map");
        initLayers(element);
    }

    virtual void draw(sf::RenderTarget& tg, sf::RenderStates state) const {
        for (Layer L : layers) {
            for (sf::Sprite T : L.tiles) {
                tg.draw(T);
            }
        }
    }

private:
    std::string PATH = "../resources/maps/";
    int firstTileID;

    sf::Vector2f tileSize;
    sf::Vector2f mapTiles;
    sf::Vector2i tilesetArray;
    sf::FloatRect drawingBound;
    sf::Texture* texture;
    sf::Vector3f mapPosition;
    std::vector<Layer> layers;
    std::vector<sf::IntRect> subRects;

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
        XMLDocument doc;
        doc.LoadFile(FILE);
        XMLElement* e = doc.FirstChildElement("tileset");

        int S = 1;
        int N = 1;
        e->QueryIntAttribute("tilecount", &S);
        e->QueryIntAttribute("columns", &N);

        int M = S / N;

        int margin = 0;
        int spacing = 0;

        e->QueryIntAttribute("margin", &margin);
        e->QueryIntAttribute("spacing", &spacing);

        int tilewidth = 1;
        int tileheight = 1;
        e->QueryIntAttribute("tilewidth", &tilewidth);
        e->QueryIntAttribute("tileheight", &tileheight);

        tileSize.x = tilewidth;
        tileSize.y = tileheight;

        for (int y = 0; y < M; y++) {
            for (int x = 0; x < N; x++) {
                sf::IntRect rect;

                rect.left = margin + (spacing + tilewidth) * x;
                rect.top = margin + (spacing + tileheight) * y;
                rect.width = tilewidth;
                rect.height = tileheight;

                subRects.push_back(rect);
            }
        }

        e = e->FirstChildElement("image");
        std::string PF = PATH + e->Attribute("source");
        texture = new sf::Texture;
        texture->loadFromFile(PF);
    }

    sf::Color hexToColor(const char* hexstring) {
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

        return sf::Color(r, g, b, a);
    }

    //FIXME: map2 - incorrect draw, map3 - vector subscription out range
    //TODO: need logger
    void initLayers(XMLElement* root) {

        XMLElement* e = root->FirstChildElement("group");

        while (strcmp(e->Attribute("name"), "tiles") != 0) {
            e = e->NextSiblingElement("group");
        }

        //TODO: loop this for N layers
        e = e->FirstChildElement("layer");
        Layer layer;

        int width = 1;
        int height = 1;
        float opacity = 1.0f;
        const char* tintcolor = "#ffffffff";
        sf::Color color(255, 255, 255, 255);
        e->QueryIntAttribute("width", &width);
        e->QueryIntAttribute("height", &height);
        e->QueryFloatAttribute("opacity", &opacity);
        if (e->Attribute("tintcolor")) tintcolor = e->Attribute("tintcolor");

        layer.opacity = opacity;
        color = hexToColor(tintcolor);
        color.a = (int)(color.a * opacity);
        layer.tintcolor = color;

        XMLElement* _e = e->FirstChildElement("data");
        std::vector<int> data = parseCSV(_e->GetText());

        int x = 0;
        int y = 0;
        int i = 0;

        while (i < data.size()) {
            if (x == width) {
                x = 0;
                y++;
            }
            int subToUse = 0;
            subToUse = data[i] - firstTileID;
            if (subToUse < 0) subToUse = 0;

            sf::Sprite sprite;
            sprite.setTexture(*texture);
            sprite.setTextureRect(subRects[subToUse]);
            sprite.setPosition((float)(x * tileSize.x), (float)(y * tileSize.y));
            sprite.setColor(color);
            layer.tiles.push_back(sprite);

            x++;
            i++;
        }

        x = 0;
        y = 0;
        i = 0;

        layers.push_back(layer);

        //TODO: next iteration of loop
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



