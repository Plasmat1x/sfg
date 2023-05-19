#pragma once

#include "Frame.hpp"

namespace anim
{
    class Flipbook
    {
    public:
        Flipbook();

        /// @brief Constructor of Flipbook
        /// @param x - number frame at x 
        /// @param y - number frame at y
        /// @param w - width frame
        /// @param h - height frame
        /// @param count - count frames
        Flipbook(const int& x, const int& y,
                 const int& w, const int& h,
                 const int& count);

        ~Flipbook();

        /// @brief manual initializer of Flipbook
        /// @param x - number frame at x 
        /// @param y - number frame at y
        /// @param w - width frame
        /// @param h - height frame
        /// @param count - count frames
        void init(const int& x, const int& y,
                  const int& w, const int& h,
                  const int& count);

        /// @brief for DebugUI (ImGui)
        void debug();

        /// @brief manual cleanup
        void cleanup();

        /// @brief return size of array of frames
        /// @return int
        int size() const;

        /// @brief return array of frames
        /// @return Frame*
        Frame* frames();

    private:
        int count;
        Frame* arr;
    };
} // namespace Animation
