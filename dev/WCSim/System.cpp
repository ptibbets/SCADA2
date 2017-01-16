#include "System.h"
#include "State.h"
#include "Solver.h"
#include "TimeManager.h"
#include "PumpController.h"
#include "FanController.h"

namespace wcsim
{
    System::System()
    {
        mState[0] = 0;
        mState[1] = 0;
        mState[2] = mTo;
        mState[3] = mTo;
        mState[4] = mTo;
    }

    System & System::getInstance()
    {
        static System aInstance;
        return aInstance;
    }

    void System::setElements(RHS &vWaterPump, RHS &vFan, RHS &vWaterBlock, RHS &vHotWater, RHS &vColdWater)
    {
        mElements[0] = &vWaterPump;
        mElements[1] = &vFan;
        mElements[2] = &vWaterBlock;
        mElements[3] = &vHotWater;
        mElements[4] = &vColdWater;
        mElementsSet = true;
    }

    void System::calcNextState()
    {
        if(mElementsSet)
        {
            auto aTime = TimeManager::getInstance().getTime();
            PumpController::getInstance().setE(mState[2] - mSetPoint);
            FanController::getInstance().setE(mState[2] - mSetPoint);
            mState = Solver::solve(mElements, mState, aTime, aTime + 0.005, mStep);
        }
    }

    State System::getState()
    {
        return mState;
    }

    void System::setSetPoint(float vSetPoint)
    {
        mSetPoint = vSetPoint;
    }

    float System::getSetPoint()
    {
        return mSetPoint;
    }

    void System::setQin(float vQin)
    {
        mQin = vQin;
    }

    float System::getQin()
    {
        return mQin;
    }

    void System::setTo(float vTo)
    {
        mTo = vTo;
    }

    float System::getTo()
    {
        return mTo;
    }
}
