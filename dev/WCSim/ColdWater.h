#pragma once

#include "RHS.h"

namespace wcsim
{
    class ColdWater: public RHS
    {
        static constexpr float mMass {0.235};
        static constexpr float mWaterSpecificHeat {4190};
        static constexpr float mWaterRho {1000};
        static constexpr float mWaterFlow {1.5 / 3600};
        static constexpr float mHeatCoeff {0.1};
        static constexpr float mRadiatorSurface {3.9};
        static constexpr float mAirSpecificHeat {1005};
        static constexpr float mAirRho {1.2};
        static constexpr float mAirFlow {181 / 3600};
        static constexpr float mFirstCoeff {(mWaterFlow * mWaterRho) / mMass};
        static constexpr float mSecondCoeff {(mHeatCoeff * mRadiatorSurface) / (mMass * mWaterSpecificHeat)};
        static constexpr float mThirdCoeff {(mAirFlow * mAirRho * mAirSpecificHeat) / (mMass * mWaterSpecificHeat)};

    public:
        ColdWater() = default;
        float operator()(float vTime, State &vState) const override;
    };
}
