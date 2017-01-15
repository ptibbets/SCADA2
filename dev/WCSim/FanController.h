#pragma once

#include "Controller.h"

namespace wcsim
{
    class FanController: public Controller
    {
        FanController() = default;
        FanController(FanController const &) = delete;
        FanController & operator=(FanController const &) = delete;

    public:
        static FanController & getInstance();
    };
}
