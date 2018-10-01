#include "mainwindow.h"
#include <QApplication>

#include <ConvertFormat.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TestIconv( );
    MainWindow w;
    w.show();

    return a.exec();
}
