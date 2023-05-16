#include "Scenes/TestScene.hpp"
#include "Core/SceneManager.hpp"
#include "Core/Utils.hpp"

#include "imgui/imgui.h"
#include "imgui-SFML.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <Core/Animation/Animator.hpp>
#include <Core/Animation/AnimationSF.hpp>
#include <thread>

#include <Game/Player.hpp>

extern sf::RenderWindow* window;
extern sf::Event* event;

Animator anim;
sf::Texture texture;
sf::Sprite sprite;
bool ap = true;
sf::View view;

sf::RectangleShape rect;
sf::RectangleShape vline;
sf::RectangleShape hline;

Player p;

TestScene::TestScene()
{
    Init();
}

TestScene::~TestScene()
{
    Cleanup();
}

void TestScene::Init()
{
    view.setSize(1280, 720);
    view.setCenter(window->getSize().x / 2.f, window->getSize().y / 2.f);

    int w = 400;
    int h = 240;
    int cf = 6;
    float sp = 8.3f;
    float scale = 1.0f;

    texture.loadFromFile("../resources/image/elf/anim_wip.png");
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, w, h));
    sprite.setScale(scale, scale);

    anim.AddAnimation("IDLE", new AnimationSF(0, 0, w, h, cf, sp, &sprite));
    anim.AddAnimation("MOVE", new AnimationSF(0, 1, w, h, cf, sp, &sprite));
    anim.AddAnimation("JUMP", new  AnimationSF(0, 2, w, h, cf - 2, sp, &sprite));
    anim.AddAnimation("FALL", new AnimationSF(0, 3, w, h, cf - 2, sp, &sprite));
    anim.AddAnimation("CLIMB", new AnimationSF(0, 4, w, h, cf, sp, &sprite));
    anim.AddAnimation("ROLL", new AnimationSF(0, 5, w, h, cf + 1, sp, &sprite));

    anim.SetAnimation("IDLE");

    sprite.setOrigin(sf::Vector2f(sprite.getTextureRect().width / 2, sprite.getTextureRect().height / 2));
    sprite.setPosition(sf::Vector2f(view.getSize().x / 2, view.getSize().y / 2));

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

void TestScene::UpdateEvents()
{

}

void TestScene::UpdateInput()
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

void TestScene::Update(const float& dt)
{
    p.Update(dt);
}

void TestScene::UpdatePast(const float& dt)
{
    if (ap)
    {
        while (!anim.GetAnimation<AnimationSF>()->Play(dt))
        {
            anim.SetAnimation("IDLE");
        }
    }
}

void TestScene::UpdateFixed()
{

}

void TestScene::Debug(const float& dt)
{
    ImGui::BeginChild("Animation test");
    {
        if (ImGui::Button("||>"))
        {
            ap = !ap;
            anim.GetAnimation<AnimationSF>()->nCurrentFrame = 0;
            anim.GetAnimation<AnimationSF>()->timer = 0.f;
        }

        ImGui::SameLine();
        ImGui::Checkbox("h", &anim.GetAnimation<AnimationSF>()->hflip);
        ImGui::SameLine();
        ImGui::Checkbox("v", &anim.GetAnimation<AnimationSF>()->vflip);
        ImGui::SameLine();
        anim.Debug();
        anim.GetAnimation<AnimationSF>()->Debug();
    }
    ImGui::EndChild();
}

void TestScene::Render()
{
    window->setView(view);
    window->draw(vline);

    window->draw(rect);

    window->draw(hline);
    window->draw(p);

}

void TestScene::Cleanup()
{
}