#include "Core/Animation/Animation.hpp"

Animation::Animation()
{
    end = false;
    hflip = false;
    vflip = false;
    nCurrentFrame = -1;
    flipbook = nullptr;
    currentFrame = nullptr;
    timer = 0.0f;
    speed = 0.0f;
    freq = 0.0f;
}

Animation::Animation(const int& x,
                     const int& y,
                     const int& w,
                     const int& h,
                     const int& c,
                     const float& s)
{
    Init(x, y, w, h, c, s);
}

Animation::~Animation()
{
    if (flipbook) delete flipbook;
}

void Animation::Init(const int& x,
                     const int& y,
                     const int& w,
                     const int& h,
                     const int& c,
                     const float& s)
{
    speed = s;
    freq = 1.f / s;
    timer = 0.0f;
    flipbook = new Flipbook(x, y, w, h, c);
    nCurrentFrame = 0;
    currentFrame = &flipbook->frames[nCurrentFrame];
}

Frame* Animation::Next()
{
    nCurrentFrame++;
    if (nCurrentFrame >= flipbook->count)
        if (end) nCurrentFrame = flipbook->count - 1;
        else nCurrentFrame = 0;

    currentFrame = &flipbook->frames[nCurrentFrame];
    timer = 0.f;
    return currentFrame;
}

Frame* Animation::Prev()
{
    nCurrentFrame--;
    if (nCurrentFrame < 0)
        if (end) nCurrentFrame = 0;
        else nCurrentFrame = flipbook->count - 1;

    currentFrame = &flipbook->frames[nCurrentFrame];
    timer = 0.f;
    return currentFrame;
}

#include "ImGui/imgui.h"
#include "imgui/imgui-SFML.h"
void Animation::Debug()
{
    ImGui::BeginChild("Animation");
    {
        if (ImGui::SliderInt("Frame", &nCurrentFrame, 0, flipbook->count - 1))
        {
            currentFrame = &flipbook->frames[nCurrentFrame];
            timer = 0.f;
        }
        ImGui::SeparatorText("Flipbook data");
        flipbook->Debug();
        ImGui::SeparatorText("Frame data");
        ImGui::Text("x_pos = %d\nypos = %d\nwidth = %d\nheight = %d", currentFrame->x, currentFrame->y, currentFrame->w, currentFrame->h);
        //ImGui::Text("Frame number = %d", currentFrame->n);

        ImGui::SeparatorText("Animation data");
        ImGui::Text("speed = %f\nfrequence = %f\ntimer = %f", speed, freq, timer);
    }
    ImGui::EndChild();
}

