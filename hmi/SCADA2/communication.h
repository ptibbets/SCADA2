#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "CommunicationData.h"
#include <qstring.h>
#include <termios.h>

class Communication
{
    QString mDevice;
    int mUSB;
    termios mTTY;
    bool mConnected {false};

    Communication() = default;
    Communication(Communication const &) = delete;
    Communication & operator=(Communication const &) = delete;

    void openDevice();
    void setParameters();

public:
    static Communication & getInstance();

    OutData receive();
    void send(InData vInData);
    void setDevice(QString &vDevice);
    bool connect();
    void disconnect();
    bool isConnected();
};

#endif // COMMUNICATION_H
