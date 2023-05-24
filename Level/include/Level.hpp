#pragma once

#include<vector>
#include<string>
#include<tinyxml2.h>
#include<stdlib.h>
#include<sstream>

using namespace tinyxml2;

class Level {
public:
    Level();
    ~Level();

    void init(const char* FILE) {
        document.LoadFile(FILE);

        for (int i : parseCSV(getStringCSV())) {
            printf("%d ", i);
        }
    }

private:
    std::vector<Tile> tiles;
    std::vector<Object> objects;
    tinyxml2::XMLDocument document;

    std::string getStringCSV() {
        std::string data = document.FirstChildElement("map")->FirstChildElement("layer")->FirstChildElement("data")->GetText();
        return data;
    }


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
};