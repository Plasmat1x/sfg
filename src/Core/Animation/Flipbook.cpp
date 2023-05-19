#include <Core/Animation/Flipbook.hpp>
#include <Core/Animation/Frame.hpp>

#include"imgui/imgui.h"
#include"imgui/imgui-SFML.h"

namespace Animation
{
    Flipbook::Flipbook()
    {
        count = 0;
        arr = nullptr;
    }

    Flipbook::Flipbook(
        const int& x,
        const int& y,
        const int& w,
        const int& h,
        const int& c)
    {
        init(x, y, w, h, c);
    }

    Flipbook::~Flipbook()
    {
        cleanup();
    }

    void Flipbook::init(const int& x,
                        const int& y,
                        const int& w,
                        const int& h,
                        const int& c)
    {
        count = c;
        arr = new Frame[count];

        for (int i = 0; i < count; i++)
        {
            arr[i] = Frame((x + i) * w, y * h, w, h, i);
        }
    }

    void Flipbook::cleanup()
    {
        if (arr) delete[] arr;
    }

    void Flipbook::debug()
    {
        ImGui::Text("Frame count: %d", count);
    }

    int Flipbook::size() const
    {
        return this->count;
    }

    Frame* Flipbook::frames() const
    {
        return this->arr;
    }


}
