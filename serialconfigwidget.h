#ifndef SERIALCONFIGLAYOUT_H
#define SERIALCONFIGLAYOUT_H

#include <QObject>
#include <QLayout>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include "qtspcomm.h"

class serialConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit serialConfigWidget(QWidget *parent = 0);

private:
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

    QPushButton *setportbtn;

    void initializedItems();
    void layoutMannager();
//串口控件布局器
    QGridLayout *serialsetlayout;
signals:
    void serialConfigInfo(SeriStruct serialconfiginfo);
public slots:
    void getSerialConfigInfo();
public:
    void refreshPortName(QStringList portlist);
    QPushButton *scanserialportbtn;

};

#endif // SERIALCONFIGLAYOUT_H
