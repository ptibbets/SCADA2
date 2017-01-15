#include "ColdWater.h"
#include "State.h"
#include "System.h"

namespace wcsim
{
    float ColdWater::operator()(float vTime, State &vState) const
    {
        auto aTo = System::getInstance().getTo();
        return mFirstCoeff * vState[0] * (vState[3] - vState[4]) - mSecondCoeff * (vState[4] - aTo) -
                mThirdCoeff * vState[1] * (vState[4] - aTo);
    }
}
