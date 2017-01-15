#include "Controller.h"

namespace wcsim
{
    void Controller::setP(float vP)
    {
        mP = vP;
    }

    void Controller::setI(float vI)
    {
        mI = vI;
    }

    void Controller::setD(float vD)
    {
        mD = vD;
    }

    void Controller::setE(float vE)
    {
        mLastE = mE;
        mE = vE;
        mIntegrator += mE;
    }

    float Controller::getCV() const
    {
        float aCV = mP * mE + mI * mIntegrator + mD * (mE - mLastE);
        if(aCV > 1) aCV = 1;
        if(aCV < 0) aCV = 0;
        return aCV;
    }
}
