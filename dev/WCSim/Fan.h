#pragma once

#include "RHS.h"

namespace wcsim
{
    class Fan: public RHS
    {
        static constexpr float mCoeff {1.25};

    public:
        Fan() = default;
        float operator()(float vTime, State &vState) const override;
    };
}
