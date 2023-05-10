#include "Core/Animation/AnimationSF.hpp"

AnimationSF::AnimationSF() : Animation()
{
    sprite = nullptr;
}

AnimationSF::AnimationSF(const int& x, const int& y,
                         const int& w, const int& h,
                         const int& c, const float& s, sf::Sprite* t) :
    Animation()
{
    Init(x, y, w, h, c, s, t);
}

AnimationSF::~AnimationSF()
{

}

void AnimationSF::Init(const int& x, const int& y,
                       const int& w, const int& h,
                       const int& c, const float& s, sf::Sprite* t)
{
    sprite = t;
    Animation::Init(x, y, w, h, c, s);
}

void AnimationSF::Play(const float& dt)
{
    timer += dt;
    while (freq < timer)
    {
        Next();
    }
}

void AnimationSF::Update()
{
    sf::Rect rect(0, 0, 0, 0);
    rect.left = currentFrame->x;
    rect.top = currentFrame->y;
    rect.width = currentFrame->w;
    rect.height = currentFrame->h;

    if (hflip)
    {
        rect.left = currentFrame->x + currentFrame->w;
        rect.width = -currentFrame->w;
    }
    if (vflip)
    {
        rect.top = currentFrame->y + currentFrame->h;
        rect.height = -currentFrame->h;
    }

    sprite->setTextureRect(rect);
}

Frame* AnimationSF::Next()
{
    Animation::Next();
    Update();
    return currentFrame;
}

Frame* AnimationSF::Prev()
{
    Animation::Prev();
    Update();
    return currentFrame;
}

#include"imgui/imgui.h"
#include"imgui/imgui-SFML.h"
void AnimationSF::Debug()
{
    ImGui::Image(*sprite);
    ImGui::Separator();
    Animation::Debug();
    Update();
}