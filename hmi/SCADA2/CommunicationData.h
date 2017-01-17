#pragma once

namespace wcsim
{
    typedef struct _OutData
    {
        float mTime;
        float mState[5];
    } OutData;

    typedef struct
    {
        float mP;
        float mI;
        float mD;
    } PID;

    typedef struct _InData
    {
        PID mPID1;
        PID mPID2;
        float mSetPoint;
        float mPower;
        float mTo;
    } InData;
}
