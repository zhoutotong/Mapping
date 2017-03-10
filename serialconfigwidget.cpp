#include "serialconfigwidget.h"

serialConfigWidget::serialConfigWidget(QWidget *parent) : QWidget(parent)
{
    initializedItems();
    layoutMannager();
    connect(setportbtn, SIGNAL(pressed()), this, SLOT(getSerialConfigInfo()));
}

/************************************************************************
//名称：initializedItems()
//参数:NULL
//返回:NULL
//功能：初始化窗口部件
//作者：zhoutong
//日期：2017.03.09
*************************************************************************/
void serialConfigWidget::initializedItems()
{
    serialsetlayout = new QGridLayout();
    serialnamecombobox = new QComboBox;
    serialnamecombobox->addItems(QStringList());
    serialbaudcombobox = new QComboBox;
    serialbaudcombobox->addItems(QStringList({"1200", "2400", "4800", "9600", "38400", "57600", "115200"}));
    serialbaudcombobox->setCurrentIndex(6);
    serialstopbitscombobox = new QComboBox;
    serialstopbitscombobox->addItems(QStringList({"1", "1.5", "2"}));
    serialstopbitscombobox->setCurrentIndex(0);
    serialdatabitcombobox = new QComboBox;
    serialdatabitcombobox->addItems(QStringList({"5", "6", "7", "8"}));
    serialdatabitcombobox->setCurrentIndex(3);
    serialcheckbitcombobox = new QComboBox;
    serialcheckbitcombobox->addItems(QStringList({"None", "Odd", "Even", "Mark", "Space"}));
    serialcheckbitcombobox->setCurrentIndex(0);
    serialflowctrcombobox = new QComboBox;
    serialflowctrcombobox->addItems(QStringList({"Hardware", "Software", "None"}));
    serialflowctrcombobox->setCurrentIndex(2);

    serialnamelabel = new QLabel("串口号");
    serialbaudlabel = new QLabel("波特率");
    serialstopbitslabel = new QLabel("停止位");
    serialdatabitlabel = new QLabel("数据位");
    serialcheckbitlabel = new QLabel("校验位");
    serialflowctrlabel = new QLabel("流控制");

    scanserialportbtn = new QPushButton("刷新串口");
    setportbtn = new QPushButton("确定");
}
/************************************************************************
//名称：layoutmannager()
//参数:NULL
//返回:NULL
//功能：串口布局管理
//作者：zhoutong
//日期：2017.03.09
*************************************************************************/
void serialConfigWidget::layoutMannager()
{
    QGridLayout *sericonfiglayout = new QGridLayout;
    QGridLayout *sericonfigbtnlayout = new QGridLayout;
    sericonfiglayout->addWidget(serialnamelabel, 1, 1);
    sericonfiglayout->addWidget(serialnamecombobox, 1, 2);           //serialsetlayout中添加串口控件
    sericonfiglayout->addWidget(serialbaudlabel, 2, 1);
    sericonfiglayout->addWidget(serialbaudcombobox, 2, 2);
    sericonfiglayout->addWidget(serialstopbitslabel, 3, 1);
    sericonfiglayout->addWidget(serialstopbitscombobox, 3, 2);
    sericonfiglayout->addWidget(serialdatabitlabel, 4, 1);
    sericonfiglayout->addWidget(serialdatabitcombobox, 4, 2);
    sericonfiglayout->addWidget(serialcheckbitlabel, 5, 1);
    sericonfiglayout->addWidget(serialcheckbitcombobox, 5, 2);
    sericonfiglayout->addWidget(serialflowctrlabel, 6, 1);
    sericonfiglayout->addWidget(serialflowctrcombobox, 6, 2);

    sericonfigbtnlayout->addWidget(scanserialportbtn, 1, 1);
    sericonfigbtnlayout->addWidget(setportbtn, 1, 2);

    serialsetlayout->addLayout(sericonfiglayout, 1, 1);
    serialsetlayout->addLayout(sericonfigbtnlayout, 2, 1);
    setLayout(serialsetlayout);
}
/************************************************************************
//名称：getSerialConfigInfo()
//参数:NULL
//返回:NULL
//功能：获取串口配置参数
//作者：zhoutong
//日期：2017.03.09
*************************************************************************/
void serialConfigWidget::getSerialConfigInfo()
{
    SeriStruct serialinfo;
    serialinfo.comName = serialnamecombobox->currentText();
    switch(serialbaudcombobox->currentText().toInt())
    {
        case 1200:
                serialinfo.baud = QSerialPort::Baud1200;
        break;
        case 2400:
                serialinfo.baud = QSerialPort::Baud2400;
        break;
        case 4800:
                serialinfo.baud = QSerialPort::Baud4800;
        break;
        case 9600:
                serialinfo.baud = QSerialPort::Baud9600;
        break;
        case 38400:
                serialinfo.baud = QSerialPort::Baud38400;
        break;
        case 57600:
                serialinfo.baud = QSerialPort::Baud57600;
        break;
        case 115200:
                serialinfo.baud = QSerialPort::Baud115200;
        break;
        default: break;
    }

    switch(serialdatabitcombobox->currentText().toInt())
    {
        case 5:
            serialinfo.databit = QSerialPort::Data5;
        break;
        case 6:
            serialinfo.databit = QSerialPort::Data6;
        break;
        case 7:
            serialinfo.databit = QSerialPort::Data7;
        break;
        case 8:
            serialinfo.databit = QSerialPort::Data8;
        break;
        default :break;
    }
    switch(serialstopbitscombobox->currentIndex())
    {
        case 0:
            serialinfo.stopbit = QSerialPort::OneStop;
            break;
        case 1:
            serialinfo.stopbit = QSerialPort::OneAndHalfStop;
            break;
        case 2:
            serialinfo.stopbit = QSerialPort::TwoStop;
            break;
        default: break;
    }

    switch(serialcheckbitcombobox->currentIndex())
    {
        case 0:
            serialinfo.checkbit = QSerialPort::NoParity;
        break;
        case 1:
            serialinfo.checkbit = QSerialPort::OddParity;
        break;
        case 2:
            serialinfo.checkbit = QSerialPort::EvenParity;
        break;
        case 3:
            serialinfo.checkbit = QSerialPort::MarkParity;
        break;
        case 4:
            serialinfo.checkbit = QSerialPort::SpaceParity;
        break;
        default:break;

    }

    switch(serialflowctrcombobox->currentIndex())
    {
        case 0:
            serialinfo.flowctr = QSerialPort::HardwareControl;
        break;
        case 1:
            serialinfo.flowctr = QSerialPort::SoftwareControl;
        break;
        case 2:
            serialinfo.flowctr = QSerialPort::NoFlowControl;
        break;
        default :break;
    }

    emit serialConfigInfo(serialinfo);
}
/************************************************************************
//名称：refreshPortName(QStringList portlist)
//参数:portlist 新的串口号列表
//返回:NULL
//功能：刷新串口列表
//作者：zhoutong
//日期：2017.03.09
*************************************************************************/
void serialConfigWidget::refreshPortName(QStringList portlist)
{
    serialnamecombobox->clear();
    serialnamecombobox->addItems(portlist);
}
