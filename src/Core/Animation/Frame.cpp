#include <Core/Animation/Frame.hpp>
#include"imgui/imgui.h"
#include"imgui/imgui-SFML.h"

namespace Animation
{
    Frame::Frame()
    {

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

    void Frame::debug()
    {
        ImGui::Text("x = %d\ny = %d\nw = %d\nh = %d\nn = %d", x, y, w, h, n);
    }

} // namespace Animation

