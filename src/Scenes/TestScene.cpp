#include "Scenes/TestScene.hpp"
#include "Core/SceneManager.hpp"
#include "Core/Utils.hpp"

#include "imgui/imgui.h"
#include "imgui-SFML.h"
#include <iostream>
#include <vector>
#include <Core/Animation/Animator.hpp>
#include <Core/Animation/AnimationSF.hpp>

extern sf::RenderWindow* window;
extern sf::Event* event;

Animator anim;
sf::Texture texture;
sf::Sprite sprite;
bool ap = true;
sf::View view;

void Anima(std::string name)
{
    anim.SetAnimation(name);
    anim.GetAnimation<AnimationSF>()->Update();
}

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
    float sp = 8.f;
    float scale = 1.f;

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
}

void TestScene::UpdateEvents()
{
    /*
    switch (event->type)
    {
    case sf::Event::KeyPressed:
        break;
    case sf::Event::KeyReleased:
        if (event->key.code == sf::Keyboard::F4)
        {
            //TODO: Action
        }
        break;
    default:
        break;
    }
    */
}

void TestScene::UpdateInput()
{

}

void TestScene::Update(const float& dt)
{
    if (ap)
    {
        anim.GetAnimation<AnimationSF>()->Play(dt);
    }
}

void TestScene::UpdatePast(const float& dt)
{
}

void TestScene::UpdateFixed()
{

}

void TestScene::Debug()
{
    ImGui::BeginChild("Animation test");
    {
        if (ImGui::Button("||>"))
        {
            ap = !ap;
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
    window->draw(sprite);
}

void TestScene::Cleanup()
{
}