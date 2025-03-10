#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "sensor_dht11.h"
#include "mqtt_connection.h"
#define TEMPERATURE_HUMIDITY_PIN 2
#define TRY_TIMES 3

int main(void) {

    if (mqtt_connect() != 0) {
        printf("Failed to connect to MQTT broker\n");
        exit(EXIT_FAILURE);
    }
    
    while (1) {
        float temperature, humidity;

        if (wiringPiSetup() == -1){
            perror("Open chip failed");
            exit(EXIT_FAILURE);
        }

        sensor_result result;
        for (int i = 0; i < TRY_TIMES; i++){
            result = get_dht11_data(TEMPERATURE_HUMIDITY_PIN);
        if (result.get_status == 0) {
            temperature = result.value.temphum.temperature;
            humidity = result.value.temphum.humidity;
            printf("Temperature: %.2f°C, Humidity: %.2f%%\n", temperature, humidity);
            char payload[50];
            snprintf(payload, 10, "%.2f", temperature);
            mqtt_publish("home/bedroom/temperature", payload);
            snprintf(payload, 10, "%.2f", humidity);
            mqtt_publish("home/bedroom/humidity", payload);
            break;
        }
        printf("Failed to get data, retry %d\n", i + 1);
        usleep(500000);
        }
        
        sleep(60); // 每60秒更新一次
    }
    
    mqtt_disconnect();


    return 0;
}