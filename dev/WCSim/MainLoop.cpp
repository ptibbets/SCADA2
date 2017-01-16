#include "MainLoop.h"
#include "TimeManager.h"
#include "Communication.h"
#include "CommunicationData.h"
#include "System.h"
#include "PumpController.h"
#include "FanController.h"

namespace wcsim
{
    void MainLoop::sendState()
    {
        OutData aOutData;
        aOutData.mTime = TimeManager::getInstance().getTime();
        auto aState = System::getInstance().getState();
        for(auto aIndex = 0; aIndex < 5; aIndex++)
        {
            aOutData.mState[aIndex] = aState[aIndex];
        }
        Communication::getInstance().sendData(aOutData);
    }

    void MainLoop::updateConfiguration(InData &vInData)
    {
        PumpController::getInstance().setP(vInData.mPID1.mP);
        PumpController::getInstance().setI(vInData.mPID1.mI);
        PumpController::getInstance().setD(vInData.mPID1.mD);
        FanController::getInstance().setP(vInData.mPID2.mP);
        FanController::getInstance().setI(vInData.mPID2.mI);
        FanController::getInstance().setD(vInData.mPID2.mD);
        System::getInstance().setSetPoint(vInData.mSetPoint);
        System::getInstance().setQin(vInData.mPower);
        System::getInstance().setTo(vInData.mTo);
    }

    MainLoop & MainLoop::getInstance()
    {
        static MainLoop aInstance;
        return aInstance;
    }

    void MainLoop::nextIter()
    {
        sendState();
        if(Communication::getInstance().isNewDataAvailable())
        {
            auto aInData = Communication::getInstance().getInData();
            updateConfiguration(aInData);
        }
        System::getInstance().calcNextState();
        auto aTime = TimeManager::getInstance().getTime() * 1000;
        aTime = (aTime / 5 + 1) * 0.005;
        TimeManager::getInstance().sleepUntil(aTime);
    }
}
