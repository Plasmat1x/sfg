#include <Core/Animation/Animator.hpp>
#include "Animator.hpp"

Animator::~Animator()
{
    Cleanup();
}

void Animator::AddAnimation(std::string name, Animation* animation)
{
    animations.insert(std::pair<std::string, Animation*>(name, animation));
    cur = animations.cbegin();
}

void Animator::SetAnimation(std::string name)
{
    bool hflip = false;
    bool vflip = false;

    if (currentAnimation != nullptr)
    {
        currentAnimation->nCurrentFrame = 0;
        hflip = currentAnimation->hflip;
        vflip = currentAnimation->vflip;
    }

    currentAnimation = animations.at(name);
    currentAnimation->hflip = hflip;
    currentAnimation->vflip = vflip;
    cur = animations.find(name);
}

void Animator::Cleanup()
{
    for (auto item : animations)
    {
        delete item.second;


    }
}

#include "ImGui/imgui.h"
#include "imgui/imgui-SFML.h"
#include <Core/Animation/AnimationSF.hpp>
void Animator::Debug()
{
    if (ImGui::BeginCombo("Animation", cur->first.c_str()))
    {
        for (storage::const_iterator i = animations.cbegin(); i != animations.cend(); i++)
        {
            const bool isSelected = (i == cur);

            if (ImGui::Selectable(i->first.c_str(), isSelected))
            {
                cur = i;
                SetAnimation(cur->first);
            }

            if (isSelected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
    ImGui::Separator();
}