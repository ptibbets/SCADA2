#include "WaterBlock.h"
#include "State.h"
#include "System.h"

namespace wcsim
{
    float WaterBlock::operator()(float vTime, State &vState) const
    {
        return System::getInstance().getQin() / mFirstDenominator - (vState[2] - vState[3]) / mSecondDenominator;
    }
}
