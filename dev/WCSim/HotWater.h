#pragma once

#include "RHS.h"

namespace wcsim
{
    class HotWater: public RHS
    {
        static constexpr float mMass {0.15}
        static constexpr float mSpecificHeat {4190};
        static constexpr float mThermalResistance {0.3};
        static constexpr float mFlow {1.5 / 3600};
        static constexpr float mRho {1000};
        static constexpr float mFirstCoeff {1 / (mMass * mSpecificHeat * mThermalResistance)};
        static constexpr float mSecondCoeff {(mFlow * mRho) / mMass};

    public:
        HotWater() = default;
        float operator()(float vTime, State &vState) const override;
    };

}
