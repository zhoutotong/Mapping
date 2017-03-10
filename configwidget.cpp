#include "configwidget.h"
#include "rplidardriver.h"
extern RplidarDriver *rplidar;
ConfigWidget::ConfigWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Setting");
    rplidar->findSerialPortName(serialportnamelist);
    serialconfigwidget = new serialConfigWidget;
    initializeWidget();
    layoutMannager();

    connect(serialconfigwidget->scanserialportbtn, SIGNAL(pressed()), this, SLOT(refreshPortName()));
//    connect(serialconfigwidget, SIGNAL(serialConfigInfo(SeriStruct)), rplidar, SLOT(setCommunicatPort(SeriStruct)));
}

/************************************************************************
//名称：initializewidget()
//参数:NULL
//返回:NULL
//功能：初始化窗口部件
//作者：zhoutong
//日期：2017.03.08
*************************************************************************/
void ConfigWidget::initializeWidget()
{
    toplayout = new QGridLayout(this);
    settab = new QTabWidget; //通信设置标签页

    communicatesetwidget = new QWidget();
    communicatesetlayout = new QGridLayout();          //通信设置标签页布局

    serialsetgroupbox = new QGroupBox("串口");        //串口设置组

    networksetgroupbox = new QGroupBox("网络");
    networksetlayout = new QGridLayout();

}
/************************************************************************
//名称：layoutManneger()
//参数:NULL
//返回:NULL
//功能：初始化窗口部件
//作者：zhoutong
//日期：2017.03.08
*************************************************************************/
void ConfigWidget::layoutMannager()
{
    toplayout->addWidget(settab, 1, 1);                             //窗口主布局
//    serialconfiglayout = new serialConfigLayout;

    QGridLayout *serialsetlayout = new QGridLayout;

    settab->addTab(communicatesetwidget, "通信");                   //将通信设置标签添加至tab中
    communicatesetwidget->setLayout(communicatesetlayout);
    communicatesetlayout->addWidget(serialsetgroupbox, 1, 1);
    serialsetlayout->addWidget(serialconfigwidget);
    serialsetgroupbox->setLayout(serialsetlayout);



    communicatesetlayout->addWidget(networksetgroupbox, 1, 2);
    networksetgroupbox->setLayout(networksetlayout);                //networksetlayout中添加网络控件
}
/************************************************************************
//名称：refreshPortName()
//参数:NULL
//返回:NULL
//功能：搜索串口号
//作者：zhoutong
//日期：2017.03.09
*************************************************************************/
void ConfigWidget::refreshPortName()
{
    serialportnamelist.clear();
    rplidar->findSerialPortName(serialportnamelist);
    serialconfigwidget->refreshPortName(serialportnamelist);
}
