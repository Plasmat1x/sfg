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
    speed = 1.f / s;
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

