#pragma once

#include <array>

namespace wcsim
{
    class State;
    class RHS;

    class Solver
    {
    public:
        static State solve(std::array<RHS*, 5> const &vSystem, State &vStartState, float vStartTime,
                float vStopTime, float vStep);
    };
}
