#include "PumpController.h"

namespace wcsim
{
    PumpController & PumpController::getInstance()
    {
        static PumpController aInstance;
        return aInstance;
    }

    float PumpController::getCV() const
    {
        float aCV = mP * mE + mI * mIntegrator + mD * (mE - mLastE);
        if(aCV > 1) aCV = 1;
        if(aCV < 0.3) aCV = 0.3;
        return aCV;
    }
}
