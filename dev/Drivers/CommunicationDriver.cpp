#include "CommunicationDriver.h"
#include <CommunicationData.h>

namespace wcsim
{
    static InData aInData {};
    static OutData aOutData {};

    CommunicationDriver::CommunicationDriver() :
            Communication(this)
    {
    }

    void CommunicationDriver::sendData(OutData vOutData)
    {
        if(mDataReceived)
        {
            mDataReceived = false;
            aOutData = vOutData;
            auto aData = reinterpret_cast<uint8_t*>(&aOutData);
            HAL_UART_Transmit_IT(mUARTHandle, aData, sizeof(OutData));
        }
    }

    InData CommunicationDriver::getInData()
    {
        mNewData = false;
        return aInData;
    }

    CommunicationDriver & CommunicationDriver::getInstance()
    {
        static CommunicationDriver aInstance;
        return aInstance;
    }

    void CommunicationDriver::setUARTHandle(UART_HandleTypeDef *vHandle)
    {
        mUARTHandle = vHandle;
        auto aData = reinterpret_cast<uint8_t*>(&aInData);
        HAL_UART_Receive_IT(mUARTHandle, aData, sizeof(InData));
    }

    void CommunicationDriver::dataSent()
    {
        auto aData = reinterpret_cast<uint8_t*>(&aInData);
        HAL_UART_Receive_IT(mUARTHandle, aData, sizeof(InData));
    }

    void CommunicationDriver::dataReceived()
    {
        mNewData = true;
        mDataReceived = true;
    }
}

extern "C"
{
    void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
    {
        if(huart->RxXferCount == 0)
        {
            wcsim::CommunicationDriver::getInstance().dataReceived();
        }
    }

    void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
    {
        if(huart->TxXferCount == 0)
        {
            wcsim::CommunicationDriver::getInstance().dataSent();
        }
    }
}
