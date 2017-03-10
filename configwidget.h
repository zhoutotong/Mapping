#ifndef CONFIGWIDGET_H
#define CONFIGWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QGridLayout>
#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include "serialconfigwidget.h"

class ConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigWidget(QWidget *parent = 0);

signals:
public:
    QStringList serialportnamelist;

private:
    QGridLayout *toplayout;
    QGridLayout *communicatesetlayout;
    QTabWidget *settab;
    QWidget *communicatesetwidget;
    QGroupBox *serialsetgroupbox;
    QGroupBox *networksetgroupbox;

//网络控件布局器
    QGridLayout *networksetlayout;
//串口控件
    serialConfigWidget *serialconfigwidget;

    void initializeWidget();
    void signalsToSlots();
    void layoutMannager();
public slots:
    void refreshPortName();
};

#endif // CONFIGWIDGET_H
