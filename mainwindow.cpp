#include "mainwindow.h"
#include <QIntValidator>
#include <iostream>

extern RplidarDriver *rplidar;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mainWidget      = new QWidget;
    infoDesktop     = new QDesktopWidget;

    this->setCentralWidget(mainWidget);

    QRect desktopSize;
    desktopSize = infoDesktop->screenGeometry();
    this->setMinimumSize(desktopSize.width() * WINDOWPROPORTION, desktopSize.height() * WINDOWPROPORTION);
    this->setMaximumSize(desktopSize.width() * WINDOWPROPORTION, desktopSize.height() * WINDOWPROPORTION);


    initializewidget();
    signalstoslots();
    layoutManager();

    writeToInfoTextbrowser(tr("ready to receive data!!!"));
}

MainWindow::~MainWindow()
{
    delete clearButton;
}
/*************************************************************************
//名称：layoutManager()
//参数:NULL
//返回:NULL
//功能：将窗口部件添加至主窗口
//作者：zhoutong
//日期：2017.03.08
*************************************************************************/
void MainWindow::layoutManager()
{
    QGridLayout *mainLayout = new QGridLayout(mainWidget);
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    mainLayout->addWidget(infotextbrowser, 2, 1, 1, 4);
    mainLayout->addWidget(clearButton, 3, 1);
    mainLayout->addWidget(scanButton, 3, 2);
    mainLayout->addWidget(stopButton, 3, 3);
    mainLayout->addWidget(motopwmvalueedit, 3, 4);      //将motopwmvalue设置按钮添加至主窗口
    mainLayout->addWidget(forceScanButton, 4, 1);       //将forcescan按钮添加至主窗口
    mainLayout->addWidget(expressScanButton, 4, 2);     //将expressscan按钮添加至主窗口
    mainLayout->addWidget(configBtn, 5, 1);             //将设置按钮添加至主窗口
}
/************************************************************************
//名称：signalstoslots()
//参数:NULL
//返回:NULL
//功能：连接信号与槽
//作者：zhoutong
//日期：2017.03.08
*************************************************************************/
void MainWindow::signalstoslots()
{
    connect(clearButton, SIGNAL(released()), infotextbrowser, SLOT(clear()));
    connect(scanButton, SIGNAL(released()), this, SLOT(sendCMDScan()));
    connect(stopButton, SIGNAL(released()), this, SLOT(sendCMDStop()));
    connect(forceScanButton, SIGNAL(released()), this, SLOT(sendCMDForceScan()));
    connect(expressScanButton, SIGNAL(released()), this, SLOT(sendCMDExpressScan()));
    connect(configBtn, SIGNAL(pressed()), configwidget, SLOT(show()));
}
/************************************************************************
//名称：initializewidget()
//参数:NULL
//返回:NULL
//功能：初始化窗口部件
//作者：zhoutong
//日期：2017.03.08
*************************************************************************/
void MainWindow::initializewidget()
{
    infotextbrowser = new QTextBrowser;
    infotextbrowser->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    configwidget    = new ConfigWidget;
    configBtn       = new QPushButton(tr("config"));

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

