#include "Frame.hpp"

namespace anim
{
    Frame::Frame()
    {
        this->x = -1;
        this->y = -1;
        this->w = -1;
        this->h = -1;
        this->n = -1;
    }

    Frame::Frame(const int& x, const int& y,
                 const int& w, const int& h,
                 const int& n)
    {
        this->x = x;
        this->y = y;
        this->w = w;
        this->h = h;
        this->n = n;

    }
} // namespace Animation

