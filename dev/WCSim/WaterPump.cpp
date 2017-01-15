#include "WaterPump.h"
#include "State.h"
#include "PumpController.h"

namespace wcsim
{
    float WaterPump::operator()(float vTime, State &vState) const
    {
        return mCoeff * (PumpController::getInstance().getCV() - vState[0]);
    }
}
