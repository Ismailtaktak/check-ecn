#include <QtGui/QApplication>
#include <QWindowsStyle>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("check ECN");
    a.setApplicationVersion("0.2");
    MainWindow w;
    w.show();

    return a.exec();
}
