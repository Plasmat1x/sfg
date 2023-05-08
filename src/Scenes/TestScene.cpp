#include "Scenes/TestScene.hpp"
#include "Core/SceneManager.hpp"
#include "Core/Utils.hpp"

#include "imgui/imgui.h"
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
    ImGui::Begin("Animation test");
    {

        if (ImGui::CollapsingHeader("Frame"))
        {
            ImGui::Text("x = %d", anim.GetAnimation<AnimationSF>()->currentFrame->x);
            ImGui::Text("y = %d", anim.GetAnimation<AnimationSF>()->currentFrame->y);
            ImGui::Text("w = %d", anim.GetAnimation<AnimationSF>()->currentFrame->w);
            ImGui::Text("h = %d", anim.GetAnimation<AnimationSF>()->currentFrame->h);
            ImGui::Text("n = %d", anim.GetAnimation<AnimationSF>()->currentFrame->n);
        }
        if (ImGui::CollapsingHeader("Animation")) {
            ImGui::Text("Count = %d", anim.GetAnimation<AnimationSF>()->flipbook->count);
            ImGui::Text("number of frame = %d", anim.GetAnimation<AnimationSF>()->nCurrentFrame);
            ImGui::Text("speed = %f", anim.GetAnimation<AnimationSF>()->speed);
            ImGui::Text("Timer = %f", anim.GetAnimation<AnimationSF>()->timer);
        }

        ImGui::Separator();

        if (ImGui::Button("Prev Frame"))
        {
            anim.currentAnimation->Prev();
            ap = false;
        }

        ImGui::SameLine();
        if (ImGui::Button("Play"))
        {
            ap = !ap;
        }

        ImGui::SameLine();
        if (ImGui::Button("Next Frame"))
        {
            anim.currentAnimation->Next();
            ap = false;
        }

        ImGui::Separator();

        for (auto animation : anim.animations)
        {
            if (ImGui::Button(animation.first.c_str()))
            {
                anim.SetAnimation(animation.first);
                anim.GetAnimation<AnimationSF>()->Update();
            }
        }

        ImGui::Checkbox("hflip", &anim.GetAnimation<AnimationSF>()->hflip);
        ImGui::SameLine();
        ImGui::Checkbox("vflip", &anim.GetAnimation<AnimationSF>()->vflip);
    }
    ImGui::End();
}

void TestScene::Render()
{
    window->setView(view);
    window->draw(sprite);
    Debug();
}

void TestScene::Cleanup()
{
}