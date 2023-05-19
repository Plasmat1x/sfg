#include "TestScene.hpp"
#include <SceneManager.hpp>

#include <imgui.h>
#include <imgui-SFML.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <Animator.hpp>
#include <thread>

#include <Player.hpp>

extern sf::RenderWindow* window;
extern sf::Event* event;
sf::Texture texture;
bool ap = true;
sf::View view;

sf::RectangleShape rect;
sf::RectangleShape vline;
sf::RectangleShape hline;

Player p;

TestScene::TestScene()
{
    init();
}

TestScene::~TestScene()
{
    cleanup();
}

void TestScene::init()
{
    view.setSize(1280, 720);
    view.setCenter(window->getSize().x / 2.f, window->getSize().y / 2.f);

    int w = 400;
    int h = 240;
    int cf = 6;
    float sp = 8.3f;
    float scale = 1.0f;

    texture.loadFromFile("../resources/image/elf/anim_wip.png");

    rect.setSize(sf::Vector2f(100.f, 100.f));
    rect.setOrigin(rect.getSize().x * 0.5f, rect.getSize().y * 0.5f);
    rect.setPosition(sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2));
    rect.setFillColor(sf::Color::Green);

    vline.setSize(sf::Vector2f(1.0f, window->getView().getSize().y));
    vline.setOrigin(sf::Vector2f(vline.getSize().x / 2.f, vline.getSize().y / 2.f));
    vline.setPosition(window->getView().getCenter());
    vline.setFillColor(sf::Color(0, 0, 0, 92));

    hline.setSize(sf::Vector2f(window->getView().getSize().x, 1.0f));
    hline.setOrigin(sf::Vector2f(hline.getSize().x / 2.f, hline.getSize().y / 2.f));
    hline.setPosition(window->getView().getCenter());
    hline.setFillColor(sf::Color(0, 0, 0, 92));

    p.Init(window->getView().getCenter(), sf::Vector2f(40, 180), texture);
    p.debug = true;
}

void TestScene::updateEvents()
{

}

void TestScene::updateInput()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        p.Climb();
        p.position.y = p.position.y - 1.f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        p.direction = Player::Direction::LEFT;
        p.Move();
        p.position.x = p.position.x - 1.f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        p.Fall();
        p.position.y = p.position.y + 1.f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        p.direction = Player::Direction::RIGHT;
        p.Move();
        p.position.x = p.position.x + 1.f;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        p.Jump();

    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
    {
        p.Roll();
    }
    else
    {
        p.Idle();
    }
}

void TestScene::update(const float& dt)
{
    p.Update(dt);

    if (ap)
        p.UpdateAnimation(dt);
}

void TestScene::updatePast(const float& dt)
{
}

void TestScene::updateFixed()
{

}

void TestScene::debug(const float& dt)
{
    ImGui::BeginChild("Animation test");
    {
        if (ImGui::Button("||>"))
        {
            ap = !ap;
        }

        ImGui::SameLine();
        //ImGui::Checkbox("h", &anim.getAnimation()->isFlipH());
        ImGui::SameLine();
        //ImGui::Checkbox("v", &anim.getAnimation()->isFlipV());
        ImGui::SameLine();

        p.animator.debug();
        p.animator.getAnimation()->debug();
    }
    ImGui::EndChild();
}

void TestScene::render()
{
    window->setView(view);

    window->draw(rect);

    window->draw(p);

    window->draw(vline);
    window->draw(hline);

}

void TestScene::cleanup()
{
}