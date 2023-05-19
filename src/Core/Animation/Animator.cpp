#include <Core/Animation/Animator.hpp>
#include "Imgui/imgui.h"
#include "imgui/imgui-SFML.h"

namespace Animation
{
    Animator::Animator()
    {

    }

    Animator::~Animator()
    {
        cleanup();
    }

    Animation* Animator::addAnimation(std::string name, Animation* animation)
    {
        storage.insert(std::pair<std::string, Animation*>(name, animation));
        cur = storage.cbegin();
        if (!currentAnimation) currentAnimation = storage.begin()->second;

        return currentAnimation;
    }

    Animation* Animator::setAnimation(std::string name)
    {
        bool hflip = false;
        bool vflip = false;

        if (currentAnimation != nullptr)
        {
            currentAnimation->reset();

            hflip = currentAnimation->isFlipH();
            vflip = currentAnimation->isFlipV();
        }

        currentAnimation = storage.at(name);
        currentAnimation->setFlipH(hflip);
        currentAnimation->setFlipV(vflip);
        cur = storage.find(name);

        return currentAnimation;
    }

    Animation* Animator::getAnimation()
    {
        return currentAnimation;
    }
    Animation* Animator::getAnimation(std::string name)
    {
        return storage.at(name);
    }

    void Animator::cleanup()
    {
        for (auto item : storage)
        {
            delete item.second;
        }
    }

    Frame* Animator::getFrame() const
    {
        return currentAnimation->getCurrentFrame();
    }

    void Animator::debug()
    {
        if (ImGui::BeginCombo("Animation", cur->first.c_str()))
        {
            for (Map::const_iterator i = storage.cbegin(); i != storage.cend(); i++)
            {
                const bool isSelected = (i == cur);

                if (ImGui::Selectable(i->first.c_str(), isSelected))
                {
                    cur = i;
                    setAnimation(cur->first);
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
} // namespace Animation

