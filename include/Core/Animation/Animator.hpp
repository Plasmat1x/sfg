#pragma once

#include<map>
#include<string>

#include<Core/Interfaces/IAnimation.hpp>

class Animator
{
public:
    std::map<std::string, IAnimation*> animations;
    IAnimation* currentAnimation;

    ~Animator();

    void AddAnimation(std::string name, IAnimation* animation);
    void SetAnimation(std::string name);

    template<typename T> T* GetAnimation();
    template<typename T> T* GetAnimation(std::string name);

    void Cleanup();
};

#include <Core/Animation/Animator.inl>
