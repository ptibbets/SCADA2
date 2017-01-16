#include "Solver.h"
#include "RHS.h"
#include "State.h"

namespace wcsim
{
    State solveSystem(std::array<RHS*, 5> const &vSystem, float vStep, float vTime, State &vState)
    {
        State aNewState;
        for(std::size_t aIndex = 0; aIndex < vSystem.size(); aIndex++)
        {
            aNewState[aIndex] = vStep * (*vSystem[aIndex])(vTime, vState);
        }
        return aNewState;
    }

    State rk4(std::array<RHS*, 5> const &vSystem, float vStep, float vTime, State &vState)
    {
        auto ak1 = solveSystem(vSystem, vStep, vTime, vState);
        auto ak2 = solveSystem(vSystem, vStep, vTime + vStep / 2, vState + ak1 / 2);
        auto ak3 = solveSystem(vSystem, vStep, vTime + vStep / 2, vState + ak2 / 2);
        auto ak4 = solveSystem(vSystem, vStep, vTime + vStep, vState + ak3);
        return vState + (ak1 + ak2 * 2 + ak3 * 2 + ak4) / 6;
    }

    State Solver::solve(std::array<RHS*, 5> const &vSystem, State &vStartState, float vStartTime,
            float vStopTime, float vStep)
    {
        auto aState = vStartState;
        for(auto aTime = vStartTime; aTime <= vStopTime; aTime += vStep)
        {
            aState = rk4(vSystem, vStep, aTime, aState);
        }
        return aState;
    }
}
