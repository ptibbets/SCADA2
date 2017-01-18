#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include <vector>

namespace Ui {
class MainWindow;
}

class MainLoop;

class Alarm : public QListWidgetItem
{
    int mState;

    int mLevel;

    double mValue;

public:
    Alarm(QString &vText, int vState, int vLevel, double vValue);

    int getState();

    int getLevel();

    double getValue();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QCustomPlot * getPlot();

    void registerLoop(MainLoop *vLoop);

    void resetPlot();

    std::vector<Alarm> & getAlarms();

private slots:
    void on_pbSetPIDs_released();

    void on_pbConnect_released();

    void on_pbDisconnect_released();

    void on_pbStartPlot_released();

    void on_pbStopPlot_released();

    void on_hsSetPoint_valueChanged(int value);

    void on_hsTo_valueChanged(int value);

    void on_hsPower_valueChanged(int value);

    void on_pbAddAlarm_released();

    void on_pbDeleteAlarm_released();

private:
    Ui::MainWindow *ui;

    MainLoop *mLoop;

    std::vector<Alarm> mAlarms;

    void setInData();

    int getSelectedStateForAlarm();

    int getSelectedLevelForAlarm();

    void addAlarm(int vState, int vLevel, double vValue);
};

#endif // MAINWINDOW_H
