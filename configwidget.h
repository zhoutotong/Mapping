#ifndef CONFIGWIDGET_H
#define CONFIGWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QGridLayout>
#include <QComboBox>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>

class ConfigWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigWidget(QWidget *parent = 0);

signals:

private:
    QGridLayout *toplayout;
    QGridLayout *communicatesetlayout;
    QTabWidget *settab;
    QWidget *communicatesetwidget;
    QGroupBox *serialsetgroupbox;
    QGroupBox *networksetgroupbox;
//串口控件布局器
    QGridLayout *serialsetlayout;
//网络控件布局器
    QGridLayout *networksetlayout;
//串口控件
    QComboBox *serialnamecombobox;
    QComboBox *serialbaudcombobox;
    QComboBox *serialstopbitscombobox;
    QComboBox *serialdatabitcombobox;
    QComboBox *serialcheckbitcombobox;
    QComboBox *serialflowctrcombobox;
    QLabel *serialnamelabel;
    QLabel *serialbaudlabel;
    QLabel *serialstopbitslabel;
    QLabel *serialdatabitlabel;
    QLabel *serialcheckbitlabel;
    QLabel *serialflowctrlabel;
    QPushButton *scanserialportbtn;

    void initializeWidget();
    void signalsToSlots();
    void layoutMannager();
public slots:
};

#endif // CONFIGWIDGET_H
