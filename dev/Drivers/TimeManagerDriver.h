#pragma once

#include <TimeManager.h>

namespace wcsim
{
    class TimeManagerDriver : public TimeManager
    {
        volatile float mTime {0};

        TimeManagerDriver();
        TimeManagerDriver(TimeManagerDriver const &) = delete;
        TimeManagerDriver & operator=(TimeManagerDriver const &) = delete;
        float getTime() override;
        void sleepUntil(float vTime) override;

    public:
        static TimeManagerDriver & getInstance();
        void incrementTime();
    };
}
