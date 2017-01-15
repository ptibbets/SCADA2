#pragma once

namespace wcsim
{
    class Controller
    {
        float mP {1};
        float mI {0};
        float mD {0};
        float mE {0};
        float mIntegrator {0};
        float mLastE {0};

    protected:
        Controller() = default;

    public:
        void setP(float vP);
        void setI(float vI);
        void setD(float vD);
        void setE(float vE);
        float getCV() const;
    };

}
