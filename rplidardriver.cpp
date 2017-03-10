#include "rplidardriver.h"
#include <iostream>

using namespace std;

RplidarDriver::RplidarDriver(QObject *parent) : QObject(parent)
{
    serialctr = new QtSPComm;
}

RplidarDriver::~RplidarDriver()
{

}
/************************************************************************
//名称：findSerialPortName(QString &portname)
//参数:portname:保存已找到的串口号的参数表
//返回:NULL
//功能：查找可用的串口号
//作者：zhoutong
//日期：2017.03.09
*************************************************************************/
void RplidarDriver::findSerialPortName(QStringList &portname)
{
    portname.clear();
    if(serialctr->FindPortName())
        portname = serialctr->portlist;
    else portname << "NONE";
}

void RplidarDriver::serialConfigura()
{
//    QString str;
//    string portname;

//    cout << "scan commport..." << endl;

//    if(serialctr->FindPortName()) cout << "failed to find comm!!!" << endl;
//    else{
//        str = serialctr->portlist.join("\r\n");
//        cout << str.toStdString();
//        cout << endl;
//configport:
//        cout << "select a comm please!" << endl;
//        cin >> portname;
//        serialctr->comminfo.comName = QString().fromStdString(portname);
//        cout << serialctr->comminfo.comName.toStdString() << " configura finish!!!" << endl;

//        if(serialctr->ConfigureSerialPort()){
//            cout << "wrong port name!!! select again!!!" << endl;
//            goto configport;
//        }
//        else connect(serialctr->SPCserialport, SIGNAL(readyRead()), this, SLOT(getRAWData()));
//    }
}

void RplidarDriver::getRAWData()
{


    static bool statuflag = 0;
    if(statuflag == 0){
        QByteArray rawdata = serialctr->SPCserialport->readAll();

        if(!rawdata.isEmpty()){
            if((rawdata[0] = 0xA5) && (rawdata[1] = 0x5A))
            {
                if(cmdConfirm(rawdata, begainScanAck, 7)){
                    std::cout << "begain!!!" << endl;
                    rawdata.clear();
                    statuflag = 1;
                }
            }

        }
    }
    else if(1 == statuflag){
        QByteArray rawdata = serialctr->SPCserialport->read(5);
        if(((rawdata[0] & 0x01) != ((rawdata[0] & 0x02) >> 1)) && ((rawdata[1] & 0x01) == 0x01)){

            if(rawdata[0] & 0x01) std::cout << "------------>";
            double angle = (((rawdata[2] << 7) & 0x00007fff) | ((rawdata[1] & 0xfe) >> 1)) / 64.0f;
            double distence = ((rawdata[3] & 0x000000ff) | ((rawdata[4] << 8) & 0x0000ff00)) / 4.0f;
            std::cout << "quality: " << ((rawdata[0] & 0xFC) >> 2) << " angle:" << angle << " distence:" << distence << endl;
        }
    }
    //this is a bad massage
}

void RplidarDriver::stop()
{
    QByteArray senddata;
    senddata[0] = _PKG_HEAD;
    senddata[1] = _CMD_STOP;
    serialctr->WriteSerialPort(senddata);
    rplidarWorkMode.workmode = RPLIDAR_STOP;
}

void RplidarDriver::scan()
{
    QByteArray senddata;
    senddata[0] = _PKG_HEAD;
    senddata[1] = _CMD_SCAN;
    serialctr->WriteSerialPort(senddata);
    rplidarWorkMode.workmode = RPLIDAR_WAITSCAN;
}

void RplidarDriver::expressScan()
{
    QByteArray senddata;
    senddata[0] = _PKG_HEAD;
    senddata[1] = _CMD_EXSCAN;
    serialctr->WriteSerialPort(senddata);
    rplidarWorkMode.workmode = RPLIDAR_WAITEXSCAN;
}

void RplidarDriver::forceScan()
{
    QByteArray senddata;
    senddata[0] = _PKG_HEAD;
    senddata[1] = _CMD_FOSCAN;
    serialctr->WriteSerialPort(senddata);
    rplidarWorkMode.workmode = RPLIDAR_WAITFOSCAN;
}

void RplidarDriver::setMotorPwm(int pwm)
{
    QByteArray senddata;
    int q = 0;
    senddata[0] = _PKG_HEAD;
    senddata[1] = 0xF0;
    senddata[2] = 0x02;
    senddata[3] = (pwm & 0xFF);
    senddata[4] = (pwm & 0xFF00) >> 8;
    for(int i = 0; i < 5; i++)
    {
        q ^= senddata[i];
    }
    senddata[5] = q;
    serialctr->WriteSerialPort(senddata);
}

void RplidarDriver::getinfo()
{
    QByteArray senddata;
    senddata[0] = _PKG_HEAD;
    senddata[1] = _CMD_GETINF;
    serialctr->WriteSerialPort(senddata);
    rplidarWorkMode.workmode = RPLIDAR_WAITGETINFO;
}

void RplidarDriver::gethealth()
{
    QByteArray senddata;
    senddata[0] = _PKG_HEAD;
    senddata[1] = _CMD_GETHEA;
    serialctr->WriteSerialPort(senddata);
    rplidarWorkMode.workmode = RPLIDAR_WAITGETHEALTH;
}

void RplidarDriver::getsample()
{
    QByteArray senddata;
    senddata[0] = _PKG_HEAD;
    senddata[1] = _CMD_GETSAM;
    serialctr->WriteSerialPort(senddata);
    rplidarWorkMode.workmode = RPLIDAR_WAITGETHEALTH;
}

bool RplidarDriver::cmdConfirm(QByteArray rawd, const int *cmd, int size)
{
    for(int i = 0; i < size; i++){
        if(rawd[i] != cmd[i]) return 0;//修改为：cmd[i] != rawd[i] 可消除警告，但执行结果错误
    }
    return 1;
}

/************************************************************************
//名称：setCommunicatePort(SeriStruct port)
//参数:portname:保存已找到的串口号的参数表
//返回:NULL
//功能：查找可用的串口号
//作者：zhoutong
//日期：2017.03.09
*************************************************************************/
void RplidarDriver::setCommunicatePort(SeriStruct port)
{
//    serialctr->ConfigureSerialPort(port);
}
