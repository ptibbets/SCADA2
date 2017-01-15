#pragma once

namespace wcsim
{
    class TimeManager
    {
        static TimeManager *mInstance;

        TimeManager(TimeManager const &) = delete;
        TimeManager & operator=(TimeManager const &) = delete;

    protected:
        TimeManager(TimeManager *vInstance);

    public:
        static TimeManager & getInstance();
        virtual float getTime() = 0;
        virtual void sleepUntil(float vTime) = 0;

    };
}
