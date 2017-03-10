#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <QObject>
#include "rplidardriver.h"

using namespace std;


RplidarDriver *rplidar = new RplidarDriver;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

//    rplidar = new RplidarDriver;
//    rplidar->serialConfigura();
    w.show();

    return a.exec();
}
