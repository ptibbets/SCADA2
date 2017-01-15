#pragma once

#include <Communication.h>
#include <stm32l4xx_hal.h>

namespace wcsim
{
    class CommunicationDriver : public Communication
    {
        UART_HandleTypeDef *mUARTHandle {nullptr};

        CommunicationDriver();
        ~CommunicationDriver() = default;
        CommunicationDriver(CommunicationDriver const &) = delete;
        CommunicationDriver & operator=(CommunicationDriver const &) = delete;
        void sendData(OutData vOutData) override;
        InData getInData() override;

    public:
        static CommunicationDriver & getInstance();
        void setUARTHandle(UART_HandleTypeDef *vHandle);
        void dataSent();
        void dataReceived();
    };
}
