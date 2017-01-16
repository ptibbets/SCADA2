#pragma once

#include <array>

namespace wcsim
{
    class State
    {
        std::array<float, 5> mState {{0}};

    public:
        State() = default;

        State & operator+(float vCoef)
        {
            for(std::size_t aIndex = 0; aIndex < mState.size(); aIndex++)
            {
                mState[aIndex] += vCoef;
            }
            return *this;
        }

        State & operator+(State & vOther)
        {
            for(std::size_t aIndex = 0; aIndex < mState.size(); aIndex++)
            {
                mState[aIndex] += vOther[aIndex];
            }
            return *this;
        }

        State & operator-(float vCoef)
        {
            for(std::size_t aIndex = 0; aIndex < mState.size(); aIndex++)
            {
                mState[aIndex] -= vCoef;
            }
            return *this;
        }

        State & operator-(State & vOther)
        {
            for(std::size_t aIndex = 0; aIndex < mState.size(); aIndex++)
            {
                mState[aIndex] -= vOther[aIndex];
            }
            return *this;
        }

        State & operator*(float vCoef)
        {
            for(std::size_t aIndex = 0; aIndex < mState.size(); aIndex++)
            {
                mState[aIndex] *= vCoef;
            }
            return *this;
        }

        State & operator*(State & vOther)
        {
            for(std::size_t aIndex = 0; aIndex < mState.size(); aIndex++)
            {
                mState[aIndex] *= vOther[aIndex];
            }
            return *this;
        }

        State & operator/(float vCoef)
        {
            for(std::size_t aIndex = 0; aIndex < mState.size(); aIndex++)
            {
                mState[aIndex] /= vCoef;
            }
            return *this;
        }

        State & operator/(State & vOther)
        {
            for(std::size_t aIndex = 0; aIndex < mState.size(); aIndex++)
            {
                mState[aIndex] /= vOther[aIndex];
            }
            return *this;
        }

        float & operator[](std::size_t vIndex)
        {
            return mState[vIndex];
        }
    };
}
