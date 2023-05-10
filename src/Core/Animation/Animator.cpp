#include <Core/Animation/Animator.hpp>
#include "Animator.hpp"

Animator::~Animator()
{
    Cleanup();
}

void Animator::AddAnimation(std::string name, IAnimation* animation)
{
    animations.insert(std::pair<std::string, IAnimation*>(name, animation));
    cur = animations.cbegin();
}

void Animator::SetAnimation(std::string name)
{
    currentAnimation = animations.at(name);
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
            }

            if (isSelected)
            {
                ImGui::SetItemDefaultFocus();
            }
        }
        ImGui::EndCombo();
    }
    ImGui::Separator();
    SetAnimation(cur->first);
}