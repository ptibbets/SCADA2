#pragma once

#include <array>

namespace wcsim
{
    class State
    {
        std::array<float, 5> mState {{0}};

    public:
        State() = default;

        float & operator[](std::size_t vIndex)
        {
            return mState[vIndex];
        }
    };
}
