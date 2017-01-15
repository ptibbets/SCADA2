#include "TimeManagerDriver.h"

extern "C"
{
    void HAL_SYSTICK_Callback()
    {
        wcsim::TimeManagerDriver::getInstance().incrementTime();
    }
}

namespace wcsim
{
    TimeManagerDriver::TimeManagerDriver() :
            TimeManager(this)
    {
    }

    float TimeManagerDriver::getTime()
    {
        return mTime;
    }

    void TimeManagerDriver::sleepUntil(float vTime)
    {
        while(mTime < vTime);
    }

    TimeManagerDriver & TimeManagerDriver::getInstance()
    {
        static TimeManagerDriver aInstance;
        return aInstance;
    }

    void TimeManagerDriver::incrementTime()
    {
        mTime += 0.001;
    }
}
