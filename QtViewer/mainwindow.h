#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDateTime>
#include "MQTTClient.h"
#include <json-c/json.h>
#include <string>

#define ADDRESS     "tcp://192.227.147.152:1883"
#define CLIENTID    "qtclient"
#define AUTHMETHOD  "xeonel"
#define AUTHTOKEN   "pwd"
#define TOPIC       "SensorData/CPUTempPitchRoll"
#define PAYLOAD     "Hello World!"
#define QOS         1
#define TIMEOUT     10000L

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_downButton_clicked();
    void on_upButton_clicked();
    void on_connectButton_clicked();
    void on_disconnectButton_clicked();
    void updateGraph(int value);
    void on_MQTTmessage(QString message);

    void on_temperatureButton_clicked();

    void on_pitchButton_clicked();

    void on_rollButton_clicked();

signals:
    void messageSignal(QString message);

private:
    Ui::MainWindow *ui;
    void update();
    int count, time, chosenGraph;
    MQTTClient client;
    volatile MQTTClient_deliveryToken deliveredtoken;
    double getTemp(QString payload);
    double getPitch(QString payload);
    double getRoll(QString payload);
    QString getTimeStamp(QString payload);

    friend void delivered(void *context, MQTTClient_deliveryToken dt);
    friend int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message);
    friend void connlost(void *context, char *cause);
};

void delivered(void *context, MQTTClient_deliveryToken dt);
int  msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message);
void connlost(void *context, char *cause);

#endif // MAINWINDOW_H

