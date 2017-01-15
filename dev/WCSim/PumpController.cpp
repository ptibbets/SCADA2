#include "PumpController.h"

namespace wcsim
{
    PumpController & PumpController::getInstance()
    {
        static PumpController aInstance;
        return aInstance;
    }
}
