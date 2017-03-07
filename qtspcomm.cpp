#include "qtspcomm.h"
#include <QDebug>

SeriStruct QtSPComm::comminfo = {"NULL", \
                                 QSerialPort::Baud115200, \
                                 QSerialPort::Data8, \
                                 QSerialPort::OneStop, \
                                 QSerialPort::NoParity, \
                                 QSerialPort::NoFlowControl};
//QSerialPort* QtSPComm::SPCserialport = NULL;

QtSPComm::QtSPComm(QObject *parent) : QObject(parent)
{
    serialportinfo = new QSerialPortInfo;
    SPCserialport = new QSerialPort;
}

QtSPComm::~QtSPComm()
{
    delete serialportinfo;
//    delete serialport;
}

int QtSPComm::FindPortName()
{
    foreach(*serialportinfo, QSerialPortInfo::availablePorts())
    {
        portlist << serialportinfo->portName();
    }
    if(portlist.isEmpty())
    {
        return 1;
    }
    return 0;
}

int QtSPComm::ConfigureSerialPort(SeriStruct &seristru)
{
    bool flag = 0;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        if(info.portName() == seristru.comName)
        {
            *serialportinfo = info;
            flag = 1;
            break;
        }
    }
    if(flag == 1)
    {
        if(getserialflag)
        {
            CloseSerialPort();
        }
        SPCserialport->setPort(*serialportinfo);
        if(SPCserialport->open(QIODevice::ReadWrite))
        {
            SPCserialport->setBaudRate(seristru.baud);
            SPCserialport->setParity(seristru.checkbit);
            SPCserialport->setDataBits(seristru.databit);
            SPCserialport->setStopBits(seristru.stopbit);
            SPCserialport->setFlowControl(seristru.flowctr);

            SPCserialport->clearError();
            SPCserialport->clear();

            getserialflag = 1;
            connect(SPCserialport, SIGNAL(readyRead()), this, SLOT(readyReadSlot()));
            emit SerialInfoSignal(*serialportinfo);
            return 0;
        }
        else return 1;
    }
    else return 1;
}

int QtSPComm::ConfigureSerialPort()
{
    bool flag = 0;
    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        if(info.portName() == comminfo.comName)
        {
            *serialportinfo = info;
            flag = 1;
            break;
        }
    }
    if(flag == 1)
    {
        if(getserialflag)
        {
            CloseSerialPort();
        }
        SPCserialport->setPort(*serialportinfo);
        if(SPCserialport->open(QIODevice::ReadWrite))
        {
            SPCserialport->setBaudRate(comminfo.baud);
            SPCserialport->setParity(comminfo.checkbit);
            SPCserialport->setDataBits(comminfo.databit);
            SPCserialport->setStopBits(comminfo.stopbit);
            SPCserialport->setFlowControl(comminfo.flowctr);

            SPCserialport->clearError();
            SPCserialport->clear();

            getserialflag = 1;
//            connect(SPCserialport, SIGNAL(readyRead()), this, SLOT(readyReadSlot()));
            emit SerialInfoSignal(*serialportinfo);
            return 0;
        }
        else return 1;
    }
    else return 1;
}

//void QtSPComm::readyReadSlot()
//{
//    emit SerialDataSignals(SPCserialport->readAll());
//}

int QtSPComm::WriteSerialPort(QByteArray dataaa)
{
    if(SPCserialport->isOpen())
    {
        SPCserialport->write(dataaa);
        return 0;
    }
    else return 1;
}

int QtSPComm::CloseSerialPort()
{
    if(SPCserialport->isOpen())
    {
        SPCserialport->clearError();
        SPCserialport->clear();
        SPCserialport->close();
        getserialflag = 0;
        return 0;
    }
    else return 1;
}

bool QtSPComm::isGet()
{
    return getserialflag;
}
