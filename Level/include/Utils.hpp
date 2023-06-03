#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <SFML/Graphics.hpp>


std::vector<int> parseCSV(std::string str);
sf::Color hexToColor(const char* hexstring);
std::vector<sf::Vector2f> parsePoints(std::string string);