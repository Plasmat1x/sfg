#pragma once

class Frame;

class IAnimation
{
public:

    virtual void Init(
        const int& x,
        const int& y,
        const int& w,
        const int& h,
        const int& c,
        const float& s
    ) = 0;

    virtual bool Next() = 0;
    virtual bool Prev() = 0;
};