#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainLoop;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QCustomPlot * getPlot();

    void registerLoop(MainLoop *vLoop);

    void resetPlot();

private slots:
    void on_pbSetPIDs_released();

    void on_pbConnect_released();

    void on_pbDisconnect_released();

    void on_pbStartPlot_released();

    void on_pbStopPlot_released();

    void on_hsSetPoint_valueChanged(int value);

    void on_hsTo_valueChanged(int value);

    void on_hsPower_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    MainLoop *mLoop;

    void setInData();
};

#endif // MAINWINDOW_H
