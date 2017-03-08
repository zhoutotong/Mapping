#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QDesktopWidget>
#include <QTextBrowser>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLineEdit>
#include <QComboBox>
#include <QToolBar>
#include <QComboBox>
#include <QGroupBox>
#include "qtspcomm.h"
#include "rplidardriver.h"
#include "configwidget.h"

#define WINDOWPROPORTION 0.8

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
    QDesktopWidget *infoDesktop;
    QPushButton *clearButton;
    QPushButton *scanButton;
    QPushButton *stopButton;
    QPushButton *forceScanButton;
    QPushButton *expressScanButton;
    QLineEdit *motopwmvalueedit;
    QGridLayout *mainLayout;

    QPushButton *configBtn;
    ConfigWidget *configwidget;

    void layoutManager();
    void signalstoslots();
    void initializewidget();
};

#endif // MAINWINDOW_H
