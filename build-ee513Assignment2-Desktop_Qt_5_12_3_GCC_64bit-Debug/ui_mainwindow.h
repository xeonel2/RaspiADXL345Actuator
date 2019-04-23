/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *upButton;
    QLineEdit *outputEdit;
    QCustomPlot *customPlot;
    QPushButton *downButton;
    QPlainTextEdit *outputText;
    QPushButton *connectButton;
    QPushButton *disconnectButton;
    QRadioButton *temperatureButton;
    QRadioButton *pitchButton;
    QRadioButton *rollButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(611, 462);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        upButton = new QPushButton(centralWidget);
        upButton->setObjectName(QString::fromUtf8("upButton"));
        upButton->setGeometry(QRect(420, 10, 141, 23));
        outputEdit = new QLineEdit(centralWidget);
        outputEdit->setObjectName(QString::fromUtf8("outputEdit"));
        outputEdit->setGeometry(QRect(140, 10, 271, 20));
        outputEdit->setReadOnly(true);
        customPlot = new QCustomPlot(centralWidget);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        customPlot->setGeometry(QRect(10, 40, 591, 191));
        downButton = new QPushButton(centralWidget);
        downButton->setObjectName(QString::fromUtf8("downButton"));
        downButton->setGeometry(QRect(10, 10, 121, 23));
        outputText = new QPlainTextEdit(centralWidget);
        outputText->setObjectName(QString::fromUtf8("outputText"));
        outputText->setGeometry(QRect(10, 240, 591, 111));
        outputText->setCenterOnScroll(true);
        connectButton = new QPushButton(centralWidget);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        connectButton->setGeometry(QRect(10, 360, 85, 29));
        disconnectButton = new QPushButton(centralWidget);
        disconnectButton->setObjectName(QString::fromUtf8("disconnectButton"));
        disconnectButton->setGeometry(QRect(100, 360, 141, 29));
        temperatureButton = new QRadioButton(centralWidget);
        temperatureButton->setObjectName(QString::fromUtf8("temperatureButton"));
        temperatureButton->setGeometry(QRect(250, 360, 102, 24));
        pitchButton = new QRadioButton(centralWidget);
        pitchButton->setObjectName(QString::fromUtf8("pitchButton"));
        pitchButton->setGeometry(QRect(380, 360, 102, 24));
        rollButton = new QRadioButton(centralWidget);
        rollButton->setObjectName(QString::fromUtf8("rollButton"));
        rollButton->setGeometry(QRect(490, 360, 102, 24));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 611, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        upButton->setText(QApplication::translate("MainWindow", "Up Button", nullptr));
        downButton->setText(QApplication::translate("MainWindow", "Down Button", nullptr));
        connectButton->setText(QApplication::translate("MainWindow", "Connect", nullptr));
        disconnectButton->setText(QApplication::translate("MainWindow", "Disconnect", nullptr));
        temperatureButton->setText(QApplication::translate("MainWindow", "Temperature", nullptr));
        pitchButton->setText(QApplication::translate("MainWindow", "Pitch", nullptr));
        rollButton->setText(QApplication::translate("MainWindow", "Roll", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
