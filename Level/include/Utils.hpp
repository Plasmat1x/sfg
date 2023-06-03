#pragma once

struct Point {
    float x;
    float y;
};

std::vector<int> parseCSV(std::string str);
sf::Color hexToColor(const char* hexstring);
std::vector<Point> parsePoints(std::string string);