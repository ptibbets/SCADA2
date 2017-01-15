#include "TimeManager.h"

namespace wcsim
{
    TimeManager * TimeManager::mInstance = nullptr;

    TimeManager::TimeManager(TimeManager *vInstance)
    {
        mInstance = vInstance;
    }

    TimeManager & TimeManager::getInstance()
    {
        return *mInstance;
    }
}
