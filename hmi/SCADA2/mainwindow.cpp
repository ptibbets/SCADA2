#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pbSetPIDs_released()
{

}

void MainWindow::on_pbConnect_released()
{

}

void MainWindow::on_pbDisconnect_released()
{

}
