#include "Flipbook.hpp"

namespace anim
{
    Flipbook::Flipbook()
    {
        this->count = -1;
        this->arr = nullptr;
    }

    Flipbook::Flipbook(const int& x, const int& y,
                       const int& w, const int& h,
                       const int& count)
    {
        init(x, y, w, h, count);
    }
    Flipbook::~Flipbook()
    {
        cleanup();
    }
    void Flipbook::init(const int& x, const int& y,
                        const int& w, const int& h,
                        const int& count)
    {
        this->count = count;
        this->arr = new Frame[count];
        for (int i = 0; i < count; i++)
        {
            arr[i] = Frame((x + i) * w, y * h, w, h, i);
        }
    }
    void Flipbook::debug()
    {

    }
    void Flipbook::cleanup()
    {
        if (arr) delete[] arr;
    }
    int Flipbook::size() const
    {
        return this->count;
    }
    Frame* Flipbook::frames()
    {
        return this->arr;
    }
} // namespace Animation
