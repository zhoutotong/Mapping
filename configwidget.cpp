#include "configwidget.h"

ConfigWidget::ConfigWidget(QWidget *parent) : QWidget(parent)
{
    setWindowTitle("Setting");
    initializeWidget();
    layoutMannager();
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

    serialsetlayout = new QGridLayout();
    serialnamecombobox = new QComboBox;
    serialbaudcombobox = new QComboBox;
    serialbaudcombobox->addItems(QStringList({"1200", "2400", "4800", "9600", "38400", "57600", "115200"}));
    serialstopbitscombobox = new QComboBox;
    serialstopbitscombobox->addItems(QStringList({"1", "1.5", "2"}));
    serialdatabitcombobox = new QComboBox;
    serialdatabitcombobox->addItems(QStringList({"5", "6", "7", "8"}));
    serialcheckbitcombobox = new QComboBox;
    serialcheckbitcombobox->addItems(QStringList({"None", "Odd", "Even", "Mark", "Space"}));
    serialflowctrcombobox = new QComboBox;
    serialflowctrcombobox->addItems(QStringList({"Hardware", "Software", "None"}));

    serialnamelabel = new QLabel("串口号");
    serialbaudlabel = new QLabel("波特率");
    serialstopbitslabel = new QLabel("停止位");
    serialdatabitlabel = new QLabel("数据位");
    serialcheckbitlabel = new QLabel("校验位");
    serialflowctrlabel = new QLabel("流控制");

    scanserialportbtn = new QPushButton("刷新串口");

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

    settab->addTab(communicatesetwidget, "通信");                   //将通信设置标签添加至tab中
    communicatesetwidget->setLayout(communicatesetlayout);
    communicatesetlayout->addWidget(serialsetgroupbox, 1, 1);
    serialsetgroupbox->setLayout(serialsetlayout);

    serialsetlayout->addWidget(serialnamelabel, 1, 1);
    serialsetlayout->addWidget(serialnamecombobox, 1, 2);           //serialsetlayout中添加串口控件
    serialsetlayout->addWidget(serialbaudlabel, 2, 1);
    serialsetlayout->addWidget(serialbaudcombobox, 2, 2);
    serialsetlayout->addWidget(serialstopbitslabel, 3, 1);
    serialsetlayout->addWidget(serialstopbitscombobox, 3, 2);
    serialsetlayout->addWidget(serialdatabitlabel, 4, 1);
    serialsetlayout->addWidget(serialdatabitcombobox, 4, 2);
    serialsetlayout->addWidget(serialcheckbitlabel, 5, 1);
    serialsetlayout->addWidget(serialcheckbitcombobox, 5, 2);
    serialsetlayout->addWidget(serialflowctrlabel, 6, 1);
    serialsetlayout->addWidget(serialflowctrcombobox, 6, 2);
    serialsetlayout->addWidget(scanserialportbtn, 7, 2);

    communicatesetlayout->addWidget(networksetgroupbox, 1, 2);
    networksetgroupbox->setLayout(networksetlayout);                //networksetlayout中添加网络控件
}
