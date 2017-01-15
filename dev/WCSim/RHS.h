#pragma once

namespace wcsim
{
    class State;

    class RHS
    {
    public:
        virtual float operator()(float vTime, State &vState) const = 0;
    };
}
