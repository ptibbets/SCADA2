#pragma once

namespace wcsim
{
    typedef struct _InData InData;

    class MainLoop
    {
        MainLoop() = default;
        MainLoop(MainLoop const &) = delete;
        MainLoop & operator=(MainLoop const &) = delete;

        void sendState();
        void updateConfiguration(InData &vInData);


    public:
        static MainLoop & getInstance();
        void nextIter();
    };
}
