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

bool AnimationSF::Play(const float& dt)
{
    timer += dt;
    while (freq < timer)
    {
        return Next();
    }
    return true;
}

bool AnimationSF::PlayReverse(const float& dt)
{
    timer += dt;
    while (freq < timer)
    {
        return Prev();
    }
    return true;
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

bool AnimationSF::Next()
{
    bool play = Animation::Next();
    Update();
    return play;
}

bool AnimationSF::Prev()
{
    bool play = Animation::Prev();
    Update();
    return play;
}

#include"imgui/imgui.h"
#include"imgui/imgui-SFML.h"
void AnimationSF::Debug()
{
    ImGui::SeparatorText("Texture preview");
    if (ImGui::Button("texture"))
    {
        textureInspector = !textureInspector;
    }
    if (textureInspector)
    {
        ImGui::Begin("TextureInspector", &textureInspector, ImGuiWindowFlags_HorizontalScrollbar | ImGuiWindowFlags_AlwaysVerticalScrollbar);
        {
            ImGui::Image(*sprite->getTexture());
        }
        ImGui::End();
    }
    ImGui::SeparatorText("Animation preview");
    ImGui::Image(*sprite);
    ImGui::Separator();
    Animation::Debug();
    Update();
}