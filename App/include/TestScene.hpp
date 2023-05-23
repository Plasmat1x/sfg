#pragma once

#include <IScene.hpp>
#include <SFML/Graphics.hpp>

class TestScene : public IScene {
public:
    TestScene();
    ~TestScene();

    void init();
    void updateEvents();
    void updateInput();
    void update(const float& dt);
    void updatePast(const float& dt);
    void updateFixed();
    void render();
    void cleanup();
    void debug(const float& dt);

private:
    float timer;
};