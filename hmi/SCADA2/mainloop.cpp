#include "mainloop.h"
#include "communication.h"

static InData aInData;

void MainLoop::checkAlarms(OutData &vOutData)
{
    auto& aAlarms = mWindow.getAlarms();
    for(auto& aElem : aAlarms)
    {
        if(aElem.getLevel() == 0)
        {
            if(vOutData.mState[aElem.getState()] > aElem.getValue())
            {
                mWindow.addActiveAlarm(aElem);
            }
            else
            {
                mWindow.deleteActiveAlarm(aElem);
            }
        }
        else
        {
            if(vOutData.mState[aElem.getState()] < aElem.getValue())
            {
                mWindow.addActiveAlarm(aElem);
            }
            else
            {
                mWindow.deleteActiveAlarm(aElem);
            }
        }
    }
}

MainLoop::MainLoop(QObject *vParent, MainWindow &vWindow) :
    QObject(vParent),
    mWindow(vWindow)
{
    mWindow.registerLoop(this);
    mWindow.resetPlot();
}

void MainLoop::startPlot(bool mState0, bool mState1, bool mState2, bool mState3, bool mState4)
{
    mPlot = true;
    mPlotState[0] = mState0;
    mPlotState[1] = mState1;
    mPlotState[2] = mState2;
    mPlotState[3] = mState3;
    mPlotState[4] = mState4;
    mWindow.resetPlot();
    auto aPlot = mWindow.getPlot();
    int aGraphIndex = 0;
    if(mPlotState[0])
    {
        aPlot->addGraph();
        aPlot->graph(aGraphIndex++)->setPen(QPen(QColor(0, 0, 0)));
    }
    if(mPlotState[1])
    {
        aPlot->addGraph();
        aPlot->graph(aGraphIndex++)->setPen(QPen(QColor(255, 0, 0)));
    }
    if(mPlotState[2])
    {
        aPlot->addGraph();
        aPlot->graph(aGraphIndex++)->setPen(QPen(QColor(0, 255, 0)));
    }
    if(mPlotState[3])
    {
        aPlot->addGraph();
        aPlot->graph(aGraphIndex++)->setPen(QPen(QColor(0, 0, 255)));
    }
    if(mPlotState[4])
    {
        aPlot->addGraph();
        aPlot->graph(aGraphIndex++)->setPen(QPen(QColor(255, 200, 0)));
    }
}

void MainLoop::stopPlot()
{
    mPlot = false;
}

void MainLoop::plot(OutData &vOutData)
{
    auto aPlot = mWindow.getPlot();
    int aGraphIndex = 0;
    if(mPlotState[0])
    {
        aPlot->graph(aGraphIndex)->addData(vOutData.mTime, vOutData.mState[0]);
        aPlot->graph(aGraphIndex++)->rescaleValueAxis(true);
    }
    if(mPlotState[1])
    {
        aPlot->graph(aGraphIndex)->addData(vOutData.mTime, vOutData.mState[1]);
        aPlot->graph(aGraphIndex++)->rescaleValueAxis(true);
    }
    if(mPlotState[2])
    {
        aPlot->graph(aGraphIndex)->addData(vOutData.mTime, vOutData.mState[2]);
        aPlot->graph(aGraphIndex++)->rescaleValueAxis(true);
    }
    if(mPlotState[3])
    {
        aPlot->graph(aGraphIndex)->addData(vOutData.mTime, vOutData.mState[3]);
        aPlot->graph(aGraphIndex++)->rescaleValueAxis(true);
    }
    if(mPlotState[4])
    {
        aPlot->graph(aGraphIndex)->addData(vOutData.mTime, vOutData.mState[4]);
        aPlot->graph(aGraphIndex++)->rescaleValueAxis(true);
    }
    aPlot->xAxis->setRange(vOutData.mTime, 10, Qt::AlignRight);
    aPlot->replot();
}

void MainLoop::setSendingData(InData vInData)
{
    aInData = vInData;
}

void MainLoop::nextIter()
{
    if(Communication::getInstance().isConnected())
    {
        Communication::getInstance().send(aInData);
        auto aData = Communication::getInstance().receive();
        if(mPlot)
        {
            plot(aData);
        }
        checkAlarms(aData);
    }
}
