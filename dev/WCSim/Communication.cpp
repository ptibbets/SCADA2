#include "Communication.h"

namespace wcsim
{
    Communication * Communication::mInstance = nullptr;

    Communication::Communication(Communication * vInstance)
    {
        mInstance = vInstance;
    }

    Communication & Communication::getInstance()
    {
        return *mInstance;
    }

    bool Communication::isNewDataAvailable() const
    {
        return mNewData;
    }
}
