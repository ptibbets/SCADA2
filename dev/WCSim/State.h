#pragma once

#include <array>

namespace wcsim
{
    class State
    {
        std::array<float, 5> mState {{0}};

    public:
        State() = default;

        State operator+(float vCoef)
        {
            State aNewState;
            for(std::size_t aIndex = 0; aIndex < mState.size(); aIndex++)
            {
                aNewState[aIndex] = mState[aIndex] + vCoef;
            }
            return aNewState;
        }

        State operator+(State & vOther)
        {
            State aNewState;
            for(std::size_t aIndex = 0; aIndex < mState.size(); aIndex++)
            {
                aNewState[aIndex] = mState[aIndex] + vOther[aIndex];
            }
            return aNewState;
        }

        State operator-(float vCoef)
        {
            State aNewState;
            for(std::size_t aIndex = 0; aIndex < mState.size(); aIndex++)
            {
                aNewState[aIndex] = mState[aIndex] - vCoef;
            }
            return aNewState;
        }

        State operator-(State & vOther)
        {
            State aNewState;
            for(std::size_t aIndex = 0; aIndex < mState.size(); aIndex++)
            {
                aNewState[aIndex] = mState[aIndex] - vOther[aIndex];
            }
            return aNewState;
        }

        State operator*(float vCoef)
        {
            State aNewState;
            for(std::size_t aIndex = 0; aIndex < mState.size(); aIndex++)
            {
                aNewState[aIndex] = mState[aIndex] * vCoef;
            }
            return aNewState;
        }

        State operator*(State & vOther)
        {
            State aNewState;
            for(std::size_t aIndex = 0; aIndex < mState.size(); aIndex++)
            {
                aNewState[aIndex] = mState[aIndex] * vOther[aIndex];
            }
            return aNewState;
        }

        State operator/(float vCoef)
        {
            State aNewState;
            for(std::size_t aIndex = 0; aIndex < mState.size(); aIndex++)
            {
                aNewState[aIndex] = mState[aIndex] / vCoef;
            }
            return aNewState;
        }

        State operator/(State & vOther)
        {
            State aNewState;
            for(std::size_t aIndex = 0; aIndex < mState.size(); aIndex++)
            {
                aNewState[aIndex] = mState[aIndex] / vOther[aIndex];
            }
            return aNewState;
        }

        float & operator[](std::size_t vIndex)
        {
            return mState[vIndex];
        }
    };
}
