#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "communication.h"
#include "CommunicationData.h"
#include "mainloop.h"

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
    setInData();
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
