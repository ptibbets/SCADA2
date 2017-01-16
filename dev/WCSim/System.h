#pragma once

#include "RHS.h"
#include "State.h"
#include <array>

namespace wcsim
{
    class System
    {
        static constexpr float mStep {0.001};
        std::array<RHS*, 5> mElements {{nullptr}};
        State mState;
        float mSetPoint {80};
        float mQin {140};
        float mTo {22};
        bool mElementsSet {false};

        System();
        System(System const &) = delete;
        System & operator=(System const &) = delete;

    public:
        static System & getInstance();
        void setElements(RHS &vWaterPump, RHS &vFan, RHS &vWaterBlock, RHS &vHotWater, RHS &vColdWater);
        void calcNextState();
        State getState();
        void setSetPoint(float vSetPoint);
        float getSetPoint();
        void setQin(float vQin);
        float getQin();
        void setTo(float vTo);
        float getTo();
    };
}
