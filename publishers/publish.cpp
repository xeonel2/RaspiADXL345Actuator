// Based on the Paho C code example from www.eclipse.org/paho/
#include <iostream>
#include <sstream>
#include <fstream>
#include <string.h>
#include "MQTTClient.h"
#include "ADXL345.h"
#include <ctime>
#define  CPU_TEMP "/sys/class/thermal/thermal_zone0/temp"
using namespace std;
using namespace exploringRPi;

//Please replace the following address with the address of your server
#define ADDRESS    "tcp://192.227.147.152:1883"
#define CLIENTID   "rpipublisher"
#define AUTHMETHOD "xeonel"
#define AUTHTOKEN  "pwd"
#define TOPIC      "SensorData/CPUTempPitchRoll"
#define QOS        1
#define TIMEOUT    10000L

float getCPUTemperature() {        // get the CPU temperature
   int cpuTemp;                    // store as an int
   fstream fs;
   fs.open(CPU_TEMP, fstream::in); // read from the file
   fs >> cpuTemp;
   fs.close();
   return (((float)cpuTemp)/1000);
}

//Returns current time string
char * getTimeNow() {
    static char timebuff[50];
    time_t t = time(0);
    tm* timeNow = localtime(&t);
    sprintf(timebuff, "%02d-%02d-%04d %02d:%02d:%02d", timeNow->tm_mday, (timeNow->tm_mon) + 1, timeNow->tm_year + 1900, timeNow->tm_hour, timeNow->tm_min, timeNow->tm_sec > 59 ? 59 : timeNow->tm_sec);
    return timebuff;
}


int main(int argc, char* argv[]) {
   char str_payload[100];          // Set your max message size here
   MQTTClient client;
   MQTTClient_connectOptions opts = MQTTClient_connectOptions_initializer;
   MQTTClient_message pubmsg = MQTTClient_message_initializer;
   MQTTClient_deliveryToken token;
   MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
   opts.keepAliveInterval = 20;
   opts.cleansession = 1;
   opts.username = AUTHMETHOD;
   opts.password = AUTHTOKEN;
   int rc;
   if ((rc = MQTTClient_connect(client, &opts)) != MQTTCLIENT_SUCCESS) {
      cout << "Failed to connect, return code " << rc << endl;
      return -1;
   }

   ADXL345 sensor(1,0x53);
   sensor.setResolution(ADXL345::NORMAL);
   sensor.setRange(ADXL345::PLUSMINUS_4_G);
   sensor.readSensorState();

   sprintf(str_payload, "{\"d\":{\"CPUTemp\": %f , \"ReadingTime\": \"%s\" ,\"Pitch\": %f, \"Roll\": %f}}", getCPUTemperature(), getTimeNow(), sensor.getPitch(), sensor.getRoll());
   pubmsg.payload = str_payload;
   pubmsg.payloadlen = strlen(str_payload);
   pubmsg.qos = QOS;
   pubmsg.retained = 0;
   MQTTClient_publishMessage(client, TOPIC, &pubmsg, &token);
   cout << "Waiting for up to " << (int)(TIMEOUT/1000) <<
        " seconds for publication of " << str_payload <<
        " \non topic " << TOPIC << " for ClientID: " << CLIENTID << endl;
   rc = MQTTClient_waitForCompletion(client, token, TIMEOUT);
   cout << "Message with token " << (int)token << " delivered." << endl;
   MQTTClient_disconnect(client, 10000);
   MQTTClient_destroy(&client);
   return rc;
}
