#include "Core/Animation/Animation.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

namespace Animation
{
    Animation::Animation()
    {
        looped = false;
        flip_h = false;
        flip_v = false;
        nCurrentFrame = -1;
        timer = 0.0f;
        speed = 0.0f;
        frequence = 0.0f;
        currentFrame = nullptr;
        flipbook = nullptr;
    }

    Animation::Animation(const int& x, const int& y,
                         const int& w, const int& h,
                         const int& count, const float& speed)
    {
        init(x, y, w, h, count, speed);
    }

    Animation::~Animation()
    {
        cleanup();
    }

    void Animation::init(const int& x, const int& y,
                         const int& w, const int& h,
                         const int& count, const float& speed)
    {
        this->looped = true;
        this->flip_h = false;
        this->flip_v = false;
        this->nCurrentFrame = 0;
        this->timer = 0.0f;
        this->speed = speed;
        this->frequence = 1.0f / speed;

        this->flipbook = new Flipbook(x, y, w, h, count);
        this->currentFrame = &flipbook->frames()[nCurrentFrame];
    }

    bool Animation::next()
    {
        nCurrentFrame++;
        if (nCurrentFrame >= flipbook->size())
            if (!looped)
            {
                nCurrentFrame = flipbook->size() - 1;
                return false;
            }
            else
            {
                nCurrentFrame = 0;
            }

        currentFrame = &flipbook->frames()[nCurrentFrame];
        timer = 0.f;
        return true;
    }
    bool Animation::prev()
    {
        nCurrentFrame--;
        if (nCurrentFrame < 0)
            if (!looped)
            {
                nCurrentFrame = 0;
                return false;
            }
            else
            {
                nCurrentFrame = flipbook->size() - 1;
            }

        currentFrame = &flipbook->frames()[nCurrentFrame];
        timer = 0.f;
        return true;
    }
    bool Animation::playForward(const float& dt)
    {
        timer += dt;
        while (frequence < timer)
        {
            return next();
        }
        return true;
    }
    bool Animation::playBackward(const float& dt)
    {
        timer += dt;
        while (frequence < timer)
        {
            return prev();
        }
        return true;
    }
    Frame* Animation::getCurrentFrame() const
    {
        return currentFrame;
    }
    bool Animation::isLooped() const
    {
        return looped;
    }
    bool Animation::isFlipH() const
    {
        return flip_h;
    }
    bool Animation::isFlipV() const
    {
        return flip_v;
    }
    void Animation::setSpeed(const float& speed)
    {
        this->speed = speed;
    }
    void Animation::setFlipH(bool flip_h)
    {
        this->flip_h = flip_h;
    }
    void Animation::setFlipV(bool flip_v)
    {
        this->flip_v = flip_v;
    }
    void Animation::cleanup()
    {
        delete flipbook;
    }
    void Animation::reset()
    {
        timer = 0.0f;
        nCurrentFrame = 0;
        currentFrame = &flipbook->frames()[nCurrentFrame];
    }
    void Animation::debug()
    {
        ImGui::BeginChild("Animation");
        {
            if (ImGui::SliderInt("Frame", &nCurrentFrame, 0, flipbook->size() - 1))
            {
                currentFrame = &flipbook->frames()[nCurrentFrame];
                timer = 0.f;
            }
            ImGui::Text("is play: %d", looped);
            ImGui::SeparatorText("Flipbook data");
            flipbook->debug();
            ImGui::SeparatorText("Frame data");
            ImGui::Text("x_pos = %d\nypos = %d\nwidth = %d\nheight = %d", currentFrame->x, currentFrame->y, currentFrame->w, currentFrame->h);

            ImGui::SeparatorText("Animation data");
            if (ImGui::SliderFloat("speed (frame per second)", &speed, 0.1f, 20.0f, "%.1f"))
            {
                frequence = 1 / speed;
            }
            ImGui::Text("frequence = %.4f\ntimer = %.4f", frequence, timer);
        }
        ImGui::EndChild();
    }
} // namespace Animation



