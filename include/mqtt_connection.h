#ifndef MQTT_CONNECTION_H
#define MQTT_CONNECTION_H

int mqtt_connect(void);
void mqtt_publish(const char* topic, const char* payload);
void mqtt_disconnect(void);

#endif // MQTT_CONNECTION_H
