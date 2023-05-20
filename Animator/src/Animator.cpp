#include "Animator.hpp"

namespace anim
{
    Animator::Animator()
    {
        currentAnimation = nullptr;
    }
    Animator::~Animator()
    {
        cleanup();
    }
    Animation* Animator::addAnimation(std::string name, Animation* animation)
    {
        storage.emplace(name, animation);
        if (!currentAnimation) currentAnimation = storage.begin()->second;
        return currentAnimation;
    }
    Animation* Animator::setAnimation(std::string name)
    {
        currentAnimation = storage.at(name);
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
        if (!storage.empty())
        {
            for (auto item : storage)
            {
                delete item.second;
            }
        }
    }
    Frame* Animator::getFrame()
    {
        return currentAnimation->getCurrentFrame();
    }
} // namespace Animation
