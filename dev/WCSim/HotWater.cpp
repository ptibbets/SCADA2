#include "HotWater.h"

namespace wcsim
{
    float HotWater::operator()(float vTime, State &vState) const
    {
        return mFirstCoeff * (vState[2] - vState[3]) - mSecondCoeff * vState[0] * (vState[3] - vState[4]);
    }
}
