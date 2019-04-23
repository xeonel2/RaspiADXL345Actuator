#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "MQTTClient.h"
#include "lib/parson.h" // using this library for json parsing as it is very lightweight and simple looking
#include <fstream>
#include <unistd.h>

#define ADDRESS     "tcp://192.227.147.152:1883"
#define CLIENTID    "rollactuator"
#define AUTHMETHOD  "xeonel"
#define AUTHTOKEN   "pwd"
#define TOPIC       "SensorData/CPUTempPitchRoll"
#define PAYLOAD     "Hello World!"
#define QOS         1
#define TIMEOUT     10000L
#define USER_LED_PATH "/sys/class/leds/led0"
#define LED_FLASH_DURATION 3
#define MICROSECOND 1000000

using namespace std;

volatile MQTTClient_deliveryToken deliveredtoken;

void delivered(void *context, MQTTClient_deliveryToken dt) {
    printf("Message with token value %d delivery confirmed\n", dt);
    deliveredtoken = dt;
}

//Flashes the LED for Duration LED_FLASH_DURATION seconds
void flashLED() {
      fstream fs;
      fs.open(USER_LED_PATH "/trigger", fstream::out);
      fs << "none";
      fs.close();
      fs.open(USER_LED_PATH "/brightness", fstream::out);
      printf("Flashing User LED coz trigger has occured!!");
      fs << "1";
      fs.flush();
      usleep(LED_FLASH_DURATION * MICROSECOND);
      fs << "0";
      fs.close();
}

void actuate(double value) {
    printf("\nActuation value: %fn\n", value);
    if (value > 55) {
        flashLED();
    }
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
    int i;
    char* payloadptr;
    char stringJson[500];
    printf("Message arrived\n");
    printf("     topic: %s\n", topicName);
    printf("   message: ");
    payloadptr = (char*) message->payload;
    for(i=0; i<message->payloadlen; i++) {
        stringJson[i] = *payloadptr++;
    }
    stringJson[i] = '\0';
    printf("%s\n", stringJson);
    JSON_Value *messageJson = json_parse_string(stringJson);
    if (messageJson != NULL) {
       JSON_Object *dObject = json_object_get_object(json_object(messageJson), "d");
       if (dObject != NULL) {
           double value = json_object_get_number(dObject, "CPUTemp");
           actuate(value);
       }
    }
    json_value_free(messageJson);
    MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
    return 1;
}

void connlost(void *context, char *cause) {
    printf("\nConnection lost\n");
    printf("     cause: %s\n", cause);
}

int main(int argc, char* argv[]) {
    MQTTClient client;
    MQTTClient_connectOptions opts = MQTTClient_connectOptions_initializer;
    int rc;
    int ch;

    MQTTClient_create(&client, ADDRESS, CLIENTID, MQTTCLIENT_PERSISTENCE_NONE, NULL);
    opts.keepAliveInterval = 20;
    opts.cleansession = 1;
    opts.username = AUTHMETHOD;
    opts.password = AUTHTOKEN;

    MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered);
    if ((rc = MQTTClient_connect(client, &opts)) != MQTTCLIENT_SUCCESS) {
        printf("Failed to connect, return code %d\n", rc);
        exit(-1);
    }
    printf("Subscribing to topic %s\nfor client %s using QoS%d\n\n"
           "Press Q<Enter> to quit\n\n", TOPIC, CLIENTID, QOS);
    MQTTClient_subscribe(client, TOPIC, QOS);

    do {
        ch = getchar();
    } while(ch!='Q' && ch != 'q');
    MQTTClient_disconnect(client, 10000);
    MQTTClient_destroy(&client);
    return rc;
}
