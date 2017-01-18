#include "mainwindow.h"
#include <QApplication>
#include "mainloop.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    MainLoop * aLoop = new MainLoop(&a, w);
    QTimer * aTimer = new QTimer(&a);
    QObject::connect(aTimer, SIGNAL(timeout()), aLoop, SLOT(nextIter()));
    aTimer->start(1);

    return a.exec();
}
