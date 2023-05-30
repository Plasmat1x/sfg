#pragma once
#include <string>
#include <unordered_map>
#include <Animation.hpp>

namespace anim {
    typedef std::unordered_map<std::string, Animation*> Map;

    class Animator {
    public:
        /// @brief Constructor <Empty>
        Animator();
        virtual ~Animator();

        /// @brief Add animation in container, if container was empty set animation at begin
        /// @param name - Key
        /// @param animation - Value
        /// @return current animation
        Animation* addAnimation(std::string name, Animation* animation);

        /// @brief set animation at Key
        /// @param name - Key
        /// @return current animation
        Animation* setAnimation(std::string name);

        /// @brief return current animation
        /// @return current animation
        Animation* getAnimation();

        /// @brief get animation at Key
        /// @param name - Key
        /// @return animation at Key
        Animation* getAnimation(std::string name);

        /// @brief manual cleanup
        void cleanup();

        /// @brief return current frame of current animation
        /// @return Frame
        Frame* getFrame();

        virtual void debug() {};
    private:
        Map storage;
        Map::const_iterator cur;
        Animation* currentAnimation;

    };
} // namespace Animation
