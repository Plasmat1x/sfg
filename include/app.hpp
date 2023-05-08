#pragma once

#include <SFML/Graphics.hpp>

extern "C"
{
#include "lua.hpp"
#include "lauxlib.h"
#include "lualib.h"
}

#include <LuaBridge/LuaBridge.h>

class App
{
public:
    int Run();

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
    bool ImDemoShow;
    bool ImControll;

    void TimerStart();
    void Cleanup();
    void Init();
    void UpdateWindow();
    void UpdateInput();
    void UpdateFixed();
    void Update();
    void UpdatePast();
    void Render();

    void Debug();
};