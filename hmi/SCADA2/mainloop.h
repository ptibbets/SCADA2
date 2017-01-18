#ifndef MAINLOOP_H
#define MAINLOOP_H

#include <QtCore>
#include "mainwindow.h"
#include "CommunicationData.h"

class MainLoop : public QObject
{
    Q_OBJECT

private:
    MainWindow &mWindow;
    bool mPlot {false};
    bool mPlotState[5] {{false}};

public:
    MainLoop(QObject *vParent, MainWindow &vWindow);

    void startPlot(bool mState0, bool mState1, bool mState2, bool mState3, bool mState4);

    void stopPlot();

    void plot(OutData &vOutData);

    void setSendingData(InData vInData);

public slots:
    void nextIter();
};

#endif // MAINLOOP_H
