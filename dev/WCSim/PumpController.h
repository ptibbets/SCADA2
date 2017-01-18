#pragma once

#include "Controller.h"

namespace wcsim
{
    class PumpController: public Controller
    {
        PumpController() = default;
        PumpController(PumpController const &) = delete;
        PumpController & operator=(PumpController const &) = delete;

    public:
        static PumpController & getInstance();
        float getCV() const override;
    };
}
