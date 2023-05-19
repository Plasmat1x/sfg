#pragma once

#include <SFML/Graphics.hpp>

class App
{
public:
    int run();

private:
    sf::Clock clock;
    sf::Clock imClock;
    sf::Time current;
    sf::Time previous;
    sf::Time eleapsed;
    sf::Time lag;
    const sf::Time MS_PER_UPDATE = sf::milliseconds(16);

    sf::View view;
    sf::Event event;
    sf::Vector2u resolution;
    float color[4];
    sf::Color WindowCollor;

    bool ImDebugShow;
    bool ImControll;

    void timerStart();
    void cleanup();
    void init();
    void updateWindow();
    void updateInput();
    void updateFixed();
    void update();
    void updatePast();
    void render();

    void debug();
};