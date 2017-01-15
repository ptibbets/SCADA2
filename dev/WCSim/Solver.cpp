#include "Solver.h"
#include "RHS.h"
#include "State.h"

namespace wcsim
{
    State Solver::solve(std::array<RHS*, 5> const &vSystem, State &vStartState, float vStartTime,
            float vStopTime, float vStep)
    {
        auto aState = vStartState;
        for(auto aTime = vStartTime; aTime <= vStopTime; aTime += vStep)
        {
            State aNewState;
            for(auto aIndex = 0; aIndex < vSystem.size(); aIndex++)
            {
                aNewState[aIndex] = (*vSystem[aIndex])(aTime, aState);
            }
            aState = aNewState;
        }
        return aState;
    }
}
