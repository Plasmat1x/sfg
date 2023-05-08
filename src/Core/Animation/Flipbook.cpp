#include <Core/Animation/Flipbook.hpp>
#include <Core/Animation/Frame.hpp>

Flipbook::Flipbook()
{
    count = 0;
    frames = nullptr;
}

Flipbook::Flipbook(
    const int& x,
    const int& y,
    const int& w,
    const int& h,
    const int& c)
{
    Init(x, y, w, h, c);
}

Flipbook::~Flipbook()
{
    if (frames) delete[] frames;
}

void Flipbook::Init(const int& x,
                    const int& y,
                    const int& w,
                    const int& h,
                    const int& c)
{
    count = c;
    frames = new Frame[count];

    for (int i = 0; i < count; i++)
    {
        frames[i] = Frame{ (x + i) * w, y * h, w, h, i };
    }
}