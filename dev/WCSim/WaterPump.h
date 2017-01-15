#pragma once

#include "RHS.h"

namespace wcsim
{
    class WaterPump: public RHS
    {
        static constexpr float mCoeff {2};

    public:
        WaterPump() = default;
        float operator()(float vTime, State &vState) const override;
    };
}
