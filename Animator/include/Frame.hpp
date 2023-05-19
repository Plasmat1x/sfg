#pragma once

namespace anim
{
    class Frame
    {
    public:
        int x = -1;
        int y = -1;
        int w = -1;
        int h = -1;
        int n = -1;

        Frame();

        /// @brief Constructor of Frame
        /// @param x - start frame at x position in pixel
        /// @param y - start frame at y position in pixel
        /// @param w - width of frame
        /// @param h - height of frame
        /// @param n - number of frame
        Frame(const int& x, const int& y,
              const int& w, const int& h,
              const int& n);

        /// @brief for Debug UI (ImGui)
        void debug();
    };
} // namespace Animation
