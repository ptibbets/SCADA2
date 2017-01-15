#include "System.h"
#include "State.h"
#include "Solver.h"
#include "TimeManager.h"

namespace wcsim
{
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
            mState = Solver::solve(mElements, mState, aTime, aTime + 0.005, mStep);
        }
    }

    State System::getState()
    {
        return mState;
    }
}
