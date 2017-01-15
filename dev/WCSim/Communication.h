#pragma once

namespace wcsim
{
    typedef struct _OutData OutData;
    typedef struct _InData InData;

    class Communication
    {
        Communication(Communication const &) = delete;
        Communication & operator=(Communication const &) = delete;

    protected:
        bool mDataSent {true};
        bool mNewData {false};
        static Communication * mInstance;

        Communication(Communication * vInstance);
        ~Communication() = default;

    public:
        static Communication & getInstance();
        virtual void sendData(OutData vOutData) = 0;
        bool isNewDataAvailable() const;
        virtual InData getInData() = 0;
    };
}
