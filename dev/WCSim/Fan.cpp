#include "Fan.h"
#include "State.h"
#include "FanController.h"

namespace wcsim
{
    float Fan::operator()(float vTime, State &vState) const
    {
        return mCoeff * (FanController::getInstance().getCV() - vState[1]);
    }
}
