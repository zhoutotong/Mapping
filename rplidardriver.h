#ifndef RPLIDARDRIVER_H
#define RPLIDARDRIVER_H

#include <QObject>
#include "qtspcomm.h"

enum {
    RPLIDAR_STOP            = 0,
    RPLIDAR_WAITSCAN        = 1,
    RPLIDAR_ENTERSCAN       = 2,
    RPLIDAR_WAITEXSCAN      = 3,
    RPLIDAR_ENTEREXSCAN     = 4,
    RPLIDAR_WAITFOSCAN      = 5,
    RPLIDAR_ENTERFOSCAN     = 6,
    RPLIDAR_WAITGETINFO     = 7,
    RPLIDAR_ENTERGETINFO    = 8,
    RPLIDAR_WAITGETHEALTH   = 9,
    RPLIDAR_ENTERGETHEALTH  = 10,
    RPLIDAR_WAITGETSAMPLE   = 11,
    RPLIDAR_ENTERGETSAMPLE  = 12,
};
typedef struct{
    uint8_t workmode = RPLIDAR_STOP;
}RplidarFlag;

class RplidarDriver : public QObject
{
    Q_OBJECT

#define _PKG_HEAD	0xA5	//数据头
#define _CMD_STOP	0x25	//进入空闲状态
#define _CMD_RESET	0x40	//测距核心软重启
#define _CMD_SCAN	0x20	//请求进入扫描采样状态
#define _CMD_EXSCAN	0x82	//请求进入扫描采样状态，并工作在最高采样频率下
#define _CMD_FOSCAN	0x21	//请求进入扫描采样状态，强制数据输出
#define _CMD_GETINF	0x50	//获取设备序列号等信息
#define _CMD_GETHEA	0x52	//获取设别健康情况
#define _CMD_GETSAM	0x59	// 获取测距用时

public:
    explicit RplidarDriver(QObject *parent = 0);
    ~RplidarDriver();

private:
    QtSPComm *serialctr;


public:
    void serialConfigura();
    void scan();
    void stop();
    void expressScan();
    void forceScan();
    void getinfo();
    void gethealth();
    void getsample();

    bool cmdConfirm(QByteArray rawd, const int *cmd, int size);

    void setMotorPwm(int pwm);

    RplidarFlag rplidarWorkMode;
public slots:
    void getRAWData();
private:
    const int begainScanAck[8]  = {0xA5, 0x5A, 0x05, 0x00, 0x00, 0x40, 0x81};
//    const int begainEXScanAck[] = {0xA5, 0x5A, 0x54, 0x00, 0x00, 0x40, 0x82};
//    const int begainFOScanAck[] = {0xA5, 0x5A, 0x05, 0x00, 0x00, 0x40, 0x81};

};





#endif // RPLIDARDRIVER_H
