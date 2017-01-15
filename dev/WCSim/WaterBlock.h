#pragma once

#include "RHS.h"

namespace wcsim
{
    class WaterBlock: public RHS
    {
        static constexpr float mSpecificHeat {710};
        static constexpr float mMass {0.01};
        static constexpr float mThermalResistance {0.3};
        static constexpr float mFirstDenominator {mSpecificHeat * mMass};
        static constexpr float mSecondDenominator {mSpecificHeat * mMass * mThermalResistance};

    public:
        WaterBlock() = default;
        float operator()(float vTime, State &vState) const override;
    };

}
