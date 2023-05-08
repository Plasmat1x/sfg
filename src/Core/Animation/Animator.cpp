#include <Core/Animation/Animator.hpp>

Animator::~Animator()
{
    Cleanup();
}

void Animator::AddAnimation(std::string name, IAnimation* animation)
{
    animations.insert(std::pair<std::string, IAnimation*>(name, animation));
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