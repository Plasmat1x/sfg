#include "Utils.hpp"

std::vector<int> parseCSV(std::string str) {
    std::vector<int> vect;

    std::stringstream ss(str);

    for (int i; ss >> i;) {
        vect.push_back(i);
        if (ss.peek() == ',')
            ss.ignore();
    }

    return vect;
}

std::vector<sf::Vector2f> parsePoints(std::string string) {
    std::vector<sf::Vector2f> res;
    std::stringstream ss(string);

    while (ss.peek() != EOF) {
        sf::Vector2f point;
        ss >> point.x;
        ss.ignore();
        ss >> point.y;
        res.push_back(point);
    }

    return res;
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