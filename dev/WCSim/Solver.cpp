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
        auto ak1State = ak1 / 2;
        ak1State = vState + ak1State;
        auto ak2 = solveSystem(vSystem, vStep, vTime + vStep / 2, ak1State);
        auto ak2State = ak2 / 2;
        ak2State = vState + ak2State;
        auto ak3 = solveSystem(vSystem, vStep, vTime + vStep / 2, ak2State);
        auto ak3State = vState + ak3;
        auto ak4 = solveSystem(vSystem, vStep, vTime + vStep, ak3State);
        auto aStateChange = ak2 + ak3;
        aStateChange = aStateChange * 2;
        aStateChange = aStateChange + ak1;
        aStateChange = aStateChange + ak4;
        aStateChange = aStateChange / 6;
        return vState + aStateChange;
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
