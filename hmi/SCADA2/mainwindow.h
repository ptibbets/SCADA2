#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pbSetPIDs_released();

    void on_pbConnect_released();

    void on_pbDisconnect_released();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
