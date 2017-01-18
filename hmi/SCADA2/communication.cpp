#include "communication.h"
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions
#include <errno.h>      // Error number definitions
#include <exception>
#include <cstdint>

void Communication::openDevice()
{
    mUSB = open(mDevice.toStdString().c_str(), O_RDWR | O_NOCTTY);
    if(mUSB < 0)
    {
        throw std::exception();
    }
    auto aResult = tcgetattr(mUSB, &mTTY);
    if(aResult != 0)
    {
        throw std::exception();
    }
}

void Communication::setParameters()
{
    cfsetospeed(&mTTY, static_cast<speed_t>(B115200));
    cfsetispeed(&mTTY, static_cast<speed_t>(B115200));
    mTTY.c_cflag &= ~PARENB;
    mTTY.c_cflag &= ~CSTOPB;
    mTTY.c_cflag &= ~CSIZE;
    mTTY.c_cflag |= CS8;
    mTTY.c_cflag &= ~CRTSCTS;
    mTTY.c_cc[VMIN] = 1;
    mTTY.c_cc[VTIME] = 10;
    mTTY.c_cflag |= CREAD | CLOCAL;
    cfmakeraw(&mTTY);

    if(tcsetattr(mUSB, TCSANOW, &mTTY) != 0)
    {
        throw std::exception();
    }
    tcflush(mUSB, TCIFLUSH);
}

Communication & Communication::getInstance()
{
    static Communication aInstance;
    return aInstance;
}


OutData Communication::receive()
{
    OutData aOutData {0, {0}};
    auto aDataPtr = reinterpret_cast<uint8_t*>(&aOutData);
    std::size_t aLen = 0;
    do
    {
        read(mUSB, &aDataPtr[aLen++], 1);
    } while(aLen < sizeof(OutData));
    return aOutData;
}

void Communication::send(InData vInData)
{
    auto aDataPtr = reinterpret_cast<uint8_t*>(&vInData);
    std::size_t aLen = 0;
    do
    {
        write(mUSB, &aDataPtr[aLen++], 1);
    } while(aLen < sizeof(InData));
}

void Communication::setDevice(QString &vDevice)
{
    mDevice = vDevice;
}

bool Communication::connect()
{
    try
    {
        openDevice();
        setParameters();
        mConnected = true;
    }
    catch (std::exception &)
    {
        mConnected = false;
    }

    return mConnected;
}

void Communication::disconnect()
{
    close(mUSB);
    mConnected = false;
}

bool Communication::isConnected()
{
    return mConnected;
}
