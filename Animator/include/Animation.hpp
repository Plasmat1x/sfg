#pragma once

#include "Frame.hpp"
#include "Flipbook.hpp"

namespace anim
{
    class Animation
    {
    public:
        Animation();

        /// @brief Constructor. Create animation with parameters for single frame
        /// @param x - number frame by x axis of spritesheet
        /// @param y - number frame by y axis of spritesheet
        /// @param w - width of frame in pixels
        /// @param h - height of frame in pixels
        /// @param count - total count frames in animation
        /// @param speed - play speed of animation in frames per second
        Animation(const int& x, const int& y,
                  const int& w, const int& h,
                  const int& count, const float& speed);

        ~Animation();

        /// @brief manual initializator. Create animation with parameters for single frame
        /// @param x - number frame by x axis of spritesheet
        /// @param y - number frame by y axis of spritesheet
        /// @param w - width of frame in pixels
        /// @param h - height of frame in pixels
        /// @param count - total count frames in animation
        /// @param speed - play speed of animation in frames per second
        void init(const int& x, const int& y,
                  const int& w, const int& h,
                  const int& count, const float& speed);

        /// @brief function for Debug GUI (ImGui)
        void debug();

        /// @brief next frame;
        /// @return true if ended playing if Flag Animation::looped == false
        bool next();

        /// @brief prevoius frame;
        /// @return true if ended playing if Flag Animation::looped == false
        bool prev();

        /// @brief play animation forward
        /// @param dt - delta time
        /// @return bool if flag looped == false, end animation and return false
        bool playForward(const float& dt);

        /// @brief play animation backwrad
        /// @param dt - delta time
        /// @return bool if flag looped == false, end animation and return false
        bool playBackward(const float& dt);

        /// @brief return current frame
        /// @return ref of Frame
        Frame* getCurrentFrame();

        /// @brief return status of flag
        /// @return Animation::looped
        bool isLooped() const;

        /// @brief return status of flag
        /// @return Animation::flip_h
        bool isFlipH() const;

        /// @brief return status of flag
        /// @return Animation::flip_v
        bool isFlipV() const;

        /// @brief set speed animation in frame per second
        /// @param speed - fps
        void setSpeed(const float& speed);

        /// @brief set horizontal flipping
        /// @param flip_h 
        void setFlipH(bool flip_h);

        /// @brief set vertical flipping
        /// @param flip_v 
        void setFlipV(bool flip_v);

        /// @brief manual cleanup
        void cleanup();

        /// @brief reset all variables to zero
        void reset();

    protected:
        bool looped;
        bool flip_h;
        bool flip_v;
        int nCurrentFrame;
        float timer;
        float speed;
        float frequence;

        Frame* currentFrame;
        Flipbook* flipbook;

    private:
    };
} // namespace Animation
