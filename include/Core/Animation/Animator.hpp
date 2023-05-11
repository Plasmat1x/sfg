#pragma once

#include<unordered_map>
#include<string>

/*
#include<Core/Interfaces/IAnimation.hpp>

typedef std::unordered_map<std::string, IAnimation*> storage;
class Animator
{
public:
    storage animations;
    IAnimation* currentAnimation;

    ~Animator();

    void AddAnimation(std::string name, IAnimation* animation);
    void SetAnimation(std::string name);

    template<typename T> T* GetAnimation();
    template<typename T> T* GetAnimation(std::string name);

    void Cleanup();

    void Debug();

private:
    storage::const_iterator cur;
};
*/

#include<Core/Animation/Animation.hpp>

typedef std::unordered_map<std::string, Animation*> storage;
class Animator
{
public:
    storage animations;
    Animation* currentAnimation;

    ~Animator();

    void AddAnimation(std::string name, Animation* animation);
    void SetAnimation(std::string name);

    template<typename T> T* GetAnimation();
    template<typename T> T* GetAnimation(std::string name);

    void Cleanup();

    void Debug();

private:
    storage::const_iterator cur;
};

#include <Core/Animation/Animator.inl>
