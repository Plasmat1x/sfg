#pragma once
#include <string>
#include <unordered_map>
#include <Animation.hpp>

namespace anim
{
    typedef std::unordered_map<std::string, Animation*> Map;

    class Animator
    {
    public:
        Animator();
        ~Animator();

        Animation* addAnimation(std::string name, Animation* animation);
        Animation* setAnimation(std::string name);
        Animation* getAnimation();
        Animation* getAnimation(std::string name);

        void debug();
        void cleanup();
        Frame* getFrame();
    private:
        Map storage;
        Map::const_iterator cur;
        Animation* currentAnimation;

    };
} // namespace Animation
