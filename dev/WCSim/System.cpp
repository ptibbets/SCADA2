#include "System.h"

namespace wcsim
{
    System * System::mInstance = nullptr;

    System::System(System *vInstance)
    {
        mInstance = vInstance;
    }
}
