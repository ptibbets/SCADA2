#pragma once

namespace wcsim
{
    typedef struct _OutData
    {
        float mTime;
    } OutData;

    typedef struct
    {
        float mP;
        float mI;
        float mD;
    } PID;

    typedef struct _InData
    {
        float mSetPoint;
        PID mPID1;
        PID mPID2;
    } InData;
}
