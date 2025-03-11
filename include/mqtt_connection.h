#ifndef MQTT_CONNECTION_H
#define MQTT_CONNECTION_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <MQTTClient.h>
#include "config.h"

int mqtt_connect(void);
void mqtt_publish(const char* topic, const char* payload);
void mqtt_disconnect(void);

#endif // MQTT_CONNECTION_H
