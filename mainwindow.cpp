#include "mainwindow.h"
#include <QIntValidator>
#include <iostream>

extern RplidarDriver *rplidar;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mainWidget = new QWidget;
    this->setCentralWidget(mainWidget);
    infotextbrowser = new QTextBrowser;
//    infotextbrowser->setMinimumSize(200, 300);
//    infotextbrowser->setMaximumSize(200, 300);
    infotextbrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
//    this->setMinimumSize(infotextbrowser->minimumSize());
//    this->setMaximumSize(infotextbrowser->maximumSize());
    writeToInfoTextbrowser(tr("ready to receive data!!!"));

    clearButton = new QPushButton(tr("clear"));
    scanButton = new QPushButton(tr("scan"));
    stopButton = new QPushButton(tr("stop"));
    forceScanButton = new QPushButton(tr("ForceScan"));
    expressScanButton = new QPushButton(tr("ExpressScan"));


    motopwmvalueedit = new QLineEdit();
    QValidator *pwmvalue = new QIntValidator(0, 65535);
    motopwmvalueedit->setMaximumWidth(40);
    motopwmvalueedit->setValidator(pwmvalue);
    motopwmvalueedit->setText(tr("660"));

    layoutManager();

    connect(clearButton, SIGNAL(released()), infotextbrowser, SLOT(clear()));
    connect(scanButton, SIGNAL(released()), this, SLOT(sendCMDScan()));
    connect(stopButton, SIGNAL(released()), this, SLOT(sendCMDStop()));
    connect(forceScanButton, SIGNAL(released()), this, SLOT(sendCMDForceScan()));
    connect(expressScanButton, SIGNAL(released()), this, SLOT(sendCMDExpressScan()));
}

MainWindow::~MainWindow()
{
    delete clearButton;
}

void MainWindow::layoutManager()
{
    QGridLayout *mainLayout = new QGridLayout(mainWidget);
    mainLayout->addWidget(infotextbrowser, 1, 1, 1, 4);
    mainLayout->addWidget(clearButton, 2, 1);
    mainLayout->addWidget(scanButton, 2, 2);
    mainLayout->addWidget(stopButton, 2, 3);
    mainLayout->addWidget(motopwmvalueedit, 2, 4);
    mainLayout->addWidget(forceScanButton, 3, 1);
    mainLayout->addWidget(expressScanButton, 3, 2);
}

void MainWindow::writeToInfoTextbrowser(QString str)
{
    infotextbrowser->insertPlainText(str);
    infotextbrowser->moveCursor(QTextCursor::End);
}

void MainWindow::receiveOriginalData(QByteArray Oridata)
{
    writeToInfoTextbrowser(QString().fromLocal8Bit(Oridata));
}

void MainWindow::sendCMDScan()
{
    int pwmstr = motopwmvalueedit->text().toInt();
    rplidar->scan();
    rplidar->setMotorPwm(pwmstr);

}

void MainWindow::sendCMDStop()
{
    rplidar->setMotorPwm(0);
    rplidar->stop();
}

void MainWindow::sendCMDForceScan()
{
    rplidar->setMotorPwm(motopwmvalueedit->text().toInt());
    rplidar->forceScan();
}

void MainWindow::sendCMDExpressScan()
{
    rplidar->setMotorPwm(motopwmvalueedit->text().toInt());
    rplidar->expressScan();
}

