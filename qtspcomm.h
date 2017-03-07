#ifndef QTSPCOMM_H
#define QTSPCOMM_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <iostream>
#include "datadef.h"

typedef struct{
    QString comName;
    qint32 baud;
    QSerialPort::DataBits databit;
    QSerialPort::StopBits stopbit;
    QSerialPort::Parity checkbit;
    QSerialPort::FlowControl flowctr;
} SeriStruct;

class QtSPComm : public QObject
{
    Q_OBJECT
public:
    explicit QtSPComm(QObject *parent = 0);
    ~QtSPComm();
    QSerialPortInfo *serialportinfo;    
    QStringList portlist;
    static SeriStruct comminfo;
    QSerialPort *SPCserialport;

    int FindPortName();
    int ConfigureSerialPort(SeriStruct &seristru);
    int ConfigureSerialPort();

    int CloseSerialPort();
    bool isGet();



private:
    bool getserialflag = 0;
signals:
    void SerialDataSignals(QByteArray);
    void SerialInfoSignal(QSerialPortInfo);

public slots:
//    void readyReadSlot();
    int WriteSerialPort(QByteArray dataaa);
};



#endif // QTSPCOMM_H
