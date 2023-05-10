#pragma once

#include "Core/Interfaces/IScene.hpp"

#include <SFML/Graphics.hpp>

class TestScene : public IScene
{
public:
    TestScene();
    ~TestScene();

    void Init();
    void UpdateEvents();
    void UpdateInput();
    void Update(const float& dt);
    void UpdatePast(const float& dt);
    void UpdateFixed();
    void Render();
    void Cleanup();
    void Debug();

private:
    float timer;
};