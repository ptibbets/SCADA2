#include "CommunicationDriver.h"
#include <CommunicationData.h>

namespace wcsim
{
    static InData aInData {};

    CommunicationDriver::CommunicationDriver() :
            Communication(this)
    {
    }

    void CommunicationDriver::sendData(OutData vOutData)
    {
        if(mDataSent)
        {
            auto aData = reinterpret_cast<uint8_t*>(&vOutData);
            HAL_UART_Transmit_IT(mUARTHandle, aData, sizeof(OutData));
        }
    }

    InData CommunicationDriver::getInData()
    {
        mNewData = false;
        auto aData = reinterpret_cast<uint8_t*>(&aInData);
        HAL_UART_Receive_IT(mUARTHandle, aData, sizeof(InData));
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
    }

    void CommunicationDriver::dataSent()
    {
        mDataSent = true;
    }

    void CommunicationDriver::dataReceived()
    {
        mNewData = true;
    }
}

extern "C"
{
    void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
    {
        if(huart->RxXferCount == sizeof(wcsim::InData))
        {
            wcsim::CommunicationDriver::getInstance().dataReceived();
        }
    }

    void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
    {
        if(huart->TxXferCount == sizeof(wcsim::OutData))
        {
            wcsim::CommunicationDriver::getInstance().dataSent();
        }
    }
}
