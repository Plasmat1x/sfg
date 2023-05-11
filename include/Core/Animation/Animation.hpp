#pragma once

#include<Core/Interfaces/IAnimation.hpp>
#include<Core/Animation/Flipbook.hpp>
#include<Core/Animation/Frame.hpp>

class Animation : public IAnimation
{
public:
    bool looped;
    bool hflip;
    bool vflip;
    int nCurrentFrame;
    float timer;
    float speed;
    float freq;
    Frame* currentFrame;
    Flipbook* flipbook;

    Animation();
    Animation(const int& x, const int& y,
              const int& w, const int& h,
              const int& c, const float& s);

    virtual ~Animation();

    virtual void Init(const int& x, const int& y,
                      const int& w, const int& h,
                      const int& c, const float& s);

    virtual bool Next();
    virtual bool Prev();

    virtual void Debug();
};