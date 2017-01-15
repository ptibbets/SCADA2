#include "WaterBlock.h"
#include "State.h"
#include "System.h"

namespace wcsim
{
    float WaterBlock::operator()(float vTime, State &vState) const
    {
        return mFirstCoeff * System::getInstance().getQin() - mSecondCoeff * (vState[2] - vState[3]);
    }
}
