#include "FanController.h"

namespace wcsim
{
    FanController & FanController::getInstance()
    {
        static FanController aInstance;
        return aInstance;
    }
}
