#pragma once

namespace wcsim
{
    class System
    {
        static System *mInstance;

        System(System const &) = delete;
        System & operator=(System const &) = delete;

    protected:
        System(System *vInstance);
        ~System() = default;

    public:
        virtual void calcNextState() = 0;
    };
}
