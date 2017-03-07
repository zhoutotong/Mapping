#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextBrowser>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include "qtspcomm.h"
#include "rplidardriver.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    QTextBrowser *infotextbrowser;
    void writeToInfoTextbrowser(QString str);
protected slots:
    void receiveOriginalData(QByteArray Oridata);
    void sendCMDScan();
    void sendCMDStop();
    void sendCMDForceScan();
    void sendCMDExpressScan();

private:
    QWidget *mainWidget;
    QPushButton *clearButton;
    QPushButton *scanButton;
    QPushButton *stopButton;
    QPushButton *forceScanButton;
    QPushButton *expressScanButton;
    QLineEdit *motopwmvalueedit;
//    QGridLayout *mainLayout;

    void layoutManager();
};

#endif // MAINWINDOW_H
