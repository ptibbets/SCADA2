#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "communication.h"
#include "CommunicationData.h"
#include "mainloop.h"

Alarm::Alarm(QString &vText, int vState, int vLevel, double vValue) :
    QListWidgetItem(vText), mState(vState), mLevel(vLevel), mValue(vValue)
{
}

int Alarm::getState()
{
    return mState;
}

int Alarm::getLevel()
{
    return mLevel;
}

double Alarm::getValue()
{
    return mValue;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pbDisconnect->setDisabled(true);
    ui->pbStartPlot->setDisabled(true);
    ui->pbStopPlot->setDisabled(true);
    ui->cbPump->setDisabled(true);
    ui->cbFan->setDisabled(true);
    ui->cbCPU->setDisabled(true);
    ui->cbHot->setDisabled(true);
    ui->cbCold->setDisabled(true);
    ui->rbPump->setChecked(true);
    ui->rbLower->setChecked(true);
    setInData();
    ui->label_15->setPixmap(QPixmap(QString::fromUtf8("/home/michal/workspace/git/SCADA2/hmi/SCADA2/hmi.png")));
    ui->label_15->setScaledContents(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


QCustomPlot * MainWindow::getPlot()
{
    return ui->plot;
}

void MainWindow::registerLoop(MainLoop *vLoop)
{
    mLoop = vLoop;
}

void MainWindow::resetPlot()
{
    delete ui->plot;
    ui->plot = new QCustomPlot(ui->tab_2);
    ui->plot->setObjectName(QStringLiteral("plot"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(ui->plot->sizePolicy().hasHeightForWidth());
    ui->plot->setSizePolicy(sizePolicy1);

    ui->verticalLayout_3->addWidget(ui->plot);
}

QList<Alarm> & MainWindow::getAlarms()
{
    return mAlarms;
}

void MainWindow::addActiveAlarm(Alarm &vAlarm)
{
    bool aExist = false;
    for(auto& aElem : mActiveAlarms)
    {
        if((vAlarm.getState() == aElem.getState()) &&
                (vAlarm.getLevel() == aElem.getLevel()) &&
                (vAlarm.getValue() == aElem.getValue()))
        {
            aExist = true;
            break;
        }
    }
    if(!aExist)
    {
        auto aAlarm = vAlarm;
        aAlarm.setForeground(Qt::red);
        mActiveAlarms.push_back(aAlarm);
        ui->activeAlarms->addItem(const_cast<Alarm*>(&mActiveAlarms.at(mActiveAlarms.size() - 1)));
    }
}

void MainWindow::deleteActiveAlarm(Alarm &vAlarm)
{
    for(auto aIndex = 0; aIndex < ui->activeAlarms->count(); aIndex++)
    {
        auto aItem = dynamic_cast<Alarm*>(ui->activeAlarms->item(aIndex));
        if(aItem != nullptr)
        {
            if((vAlarm.getState() == aItem->getState()) &&
                    (vAlarm.getLevel() == aItem->getLevel()) &&
                    (vAlarm.getValue() == aItem->getValue()))
            {
                ui->activeAlarms->removeItemWidget(aItem);
                for(auto aElem = 0; aElem < mActiveAlarms.size(); aElem++)
                {
                    if((aItem->getState() == mActiveAlarms[aIndex].getState()) &&
                            (aItem->getLevel() == mActiveAlarms[aIndex].getLevel()) &&
                            (aItem->getValue() == mActiveAlarms[aIndex].getValue()))
                    {
                        mActiveAlarms.erase(mActiveAlarms.begin() + aIndex);
                        break;
                    }
                }
                break;
            }
        }
    }
}

void MainWindow::setInData()
{
    InData aInData;
    aInData.mPID1.mP = ui->pumpPEdit->value();
    aInData.mPID1.mI = ui->pumpIEdit->value();
    aInData.mPID1.mD = ui->pumpDEdit->value();
    aInData.mPID2.mP = ui->fanPEdit->value();
    aInData.mPID2.mI = ui->fanIEdit->value();
    aInData.mPID2.mD = ui->fanDEdit->value();
    aInData.mPower = ui->hsPower->value();
    aInData.mSetPoint = ui->hsSetPoint->value();
    aInData.mTo = ui->hsTo->value();
    mLoop->setSendingData(aInData);
    ui->pumpPVal->setText(QString::number(ui->pumpPEdit->value(), 'f', 3));
    ui->pumpIVal->setText(QString::number(ui->pumpIEdit->value(), 'f', 3));
    ui->pumpDVal->setText(QString::number(ui->pumpDEdit->value(), 'f', 3));
    ui->fanPVal->setText(QString::number(ui->fanPEdit->value(), 'f', 3));
    ui->fanIVal->setText(QString::number(ui->fanIEdit->value(), 'f', 3));
    ui->fanDVal->setText(QString::number(ui->fanDEdit->value(), 'f', 3));
    ui->labSetPoint->setText(QString::number(ui->hsSetPoint->value(), 'f', 3));
    ui->labTo->setText(QString::number(ui->hsTo->value(), 'f', 3));
    ui->labPower->setText(QString::number(ui->hsPower->value(), 'f', 3));
}

int MainWindow::getSelectedStateForAlarm()
{
    if(ui->rbPump->isChecked())
    {
        return 0;
    }
    else if(ui->rbFan->isChecked())
    {
        return 1;
    }
    else if(ui->rbCPU->isChecked())
    {
        return 2;
    }
    else if(ui->rbHot->isChecked())
    {
        return 3;
    }
    else
    {
        return 4;
    }
}

int MainWindow::getSelectedLevelForAlarm()
{
    if(ui->rbHigher->isChecked())
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void MainWindow::addAlarm(int vState, int vLevel, double vValue)
{
    bool aExist = false;
    for(auto& aElem : mAlarms)
    {
        if((vState == aElem.getState()) &&
                (vLevel == aElem.getLevel()) &&
                (vValue == aElem.getValue()))
        {
            aExist = true;
            break;
        }
    }
    if(!aExist)
    {
        auto aAlarmText = getAlarmText(vState, vLevel, vValue);
        auto aAlarm = Alarm(aAlarmText, vState, vLevel, vValue);
        mAlarms.push_back(aAlarm);
        ui->allAlarms->addItem(const_cast<Alarm*>(&mAlarms.at(mAlarms.size() - 1)));
    }
}

QString MainWindow::getAlarmText(int vState, int vLevel, double vValue)
{
    QString aAlarmText;
    switch(vState)
    {
    case 0:
    {
        aAlarmText += "Pump speed ";
        break;
    }
    case 1:
    {
        aAlarmText += "Fan speed ";
        break;
    }
    case 2:
    {
        aAlarmText += "CPU temp ";
        break;
    }
    case 3:
    {
        aAlarmText += "Hot Water temp ";
        break;
    }
    case 4:
    {
        aAlarmText += "Cold Water temp";
        break;
    }
    }
    if(vLevel == 0)
    {
        aAlarmText += "higher than ";
    }
    else
    {
        aAlarmText += "lower than ";
    }
    aAlarmText += QString::number(vValue, 'f', 3);
    return aAlarmText;
}

void MainWindow::on_pbSetPIDs_released()
{
    setInData();
}

void MainWindow::on_pbConnect_released()
{
    auto aDeviceName = ui->deviceName->text();
    Communication::getInstance().setDevice(aDeviceName);
    if(Communication::getInstance().connect())
    {
        ui->pbConnect->setDisabled(true);
        ui->pbDisconnect->setEnabled(true);
        ui->pbStartPlot->setEnabled(true);
        ui->cbPump->setEnabled(true);
        ui->cbFan->setEnabled(true);
        ui->cbCPU->setEnabled(true);
        ui->cbHot->setEnabled(true);
        ui->cbCold->setEnabled(true);
    }
}

void MainWindow::on_pbDisconnect_released()
{
    Communication::getInstance().disconnect();
    ui->pbConnect->setEnabled(true);
    ui->pbDisconnect->setDisabled(true);
    ui->pbStartPlot->setDisabled(true);
    ui->pbStopPlot->setDisabled(true);
    ui->cbPump->setDisabled(true);
    ui->cbFan->setDisabled(true);
    ui->cbCPU->setDisabled(true);
    ui->cbHot->setDisabled(true);
    ui->cbCold->setDisabled(true);
}

void MainWindow::on_pbStartPlot_released()
{
    mLoop->startPlot(ui->cbPump->isChecked(),
                     ui->cbFan->isChecked(),
                     ui->cbCPU->isChecked(),
                     ui->cbHot->isChecked(),
                     ui->cbCold->isChecked());
    ui->pbStartPlot->setDisabled(true);
    ui->pbStopPlot->setEnabled(true);
    ui->cbPump->setDisabled(true);
    ui->cbFan->setDisabled(true);
    ui->cbCPU->setDisabled(true);
    ui->cbHot->setDisabled(true);
    ui->cbCold->setDisabled(true);
}

void MainWindow::on_pbStopPlot_released()
{
    mLoop->stopPlot();
    ui->pbStartPlot->setEnabled(true);
    ui->pbStopPlot->setDisabled(true);
    ui->cbPump->setEnabled(true);
    ui->cbFan->setEnabled(true);
    ui->cbCPU->setEnabled(true);
    ui->cbHot->setEnabled(true);
    ui->cbCold->setEnabled(true);
}

void MainWindow::on_hsSetPoint_valueChanged(int value)
{
    (void)value;
    setInData();
}

void MainWindow::on_hsTo_valueChanged(int value)
{
    (void)value;
    setInData();
}

void MainWindow::on_hsPower_valueChanged(int value)
{
    (void)value;
    setInData();
}

void MainWindow::on_pbAddAlarm_released()
{
    auto aState = getSelectedStateForAlarm();
    auto aLevel = getSelectedLevelForAlarm();
    addAlarm(aState, aLevel, ui->alarmValue->value());
}

void MainWindow::on_pbDeleteAlarm_released()
{
    auto aVal = ui->allAlarms->selectedItems();
    if(aVal.size() > 0)
    {
        auto aItem = dynamic_cast<Alarm*>(aVal[0]);
        if(aItem != nullptr)
        {
            for(auto aIndex = 0; aIndex < mAlarms.size(); aIndex++)
            {
                if((aItem->getState() == mAlarms[aIndex].getState()) &&
                        (aItem->getLevel() == mAlarms[aIndex].getLevel()) &&
                        (aItem->getValue() == mAlarms[aIndex].getValue()))
                {
                    mAlarms.erase(mAlarms.begin() + aIndex);
                    ui->allAlarms->removeItemWidget(aItem);
                    break;
                }
            }
        }
    }
}
