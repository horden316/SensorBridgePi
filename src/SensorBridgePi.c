#include <pthread.h>
#include <unistd.h>
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "sensor_dht11.h"
#include "sensor_sht3x.h"
#include "mqtt_connection.h"
#include "config.h"
#define TEMPERATURE_HUMIDITY_PIN 2
#define TRY_TIMES 3
#define MQTT_TRY_TIMES 5

void* sensor_thread_func(void* arg) {
    Config config = *(Config*)arg;
    while (1) {
        float temperature, humidity;
        sensor_result result;
        for (int i = 0; i < TRY_TIMES; i++) {
            //result = get_dht11_data(TEMPERATURE_HUMIDITY_PIN);
            int addr = 0x44;

            if (strcmp(config.temperature_humidity_sensor, "SHT3x") == 0) {
                result = get_sht3x_data("/dev/i2c-3", addr);
            } else if (strcmp(config.temperature_humidity_sensor, "DHT11") == 0) {
                result = get_dht11_data(TEMPERATURE_HUMIDITY_PIN);
            } else {
                printf("Unknown sensor type\n");
                exit(EXIT_FAILURE);
            }
            if (result.get_status == 0) {
                temperature = result.value.temphum.temperature;
                humidity = result.value.temphum.humidity;
                
                humidity = humidity + config.humidity_compensation; // 補償值

                printf("Temperature: %.2f°C, Humidity: %.2f%%\n", temperature, humidity);
                char payload[10];
                snprintf(payload, 10, "%.2f", temperature);
                mqtt_publish("home/bedroom/temperature", payload);
                snprintf(payload, 10, "%.2f", humidity);
                mqtt_publish("home/bedroom/humidity", payload);
                break;  
                }
            printf("Failed to get data, retry %d\n", i + 1);
            usleep(500000);
        }
        sleep(20); // 每60秒更新一次
    }
}

void* mqtt_thread_func(void* arg) {
    while (1) {
        MQTTClient_yield();
        sleep(10);
    }
}

int main(void) {

    Config config;
    if (read_config_json("config.json", &config) != 0) {
        printf("Failed to read config file\n");
        exit(EXIT_FAILURE);
    }

    u_int8_t mqtt_try_times = MQTT_TRY_TIMES;
    while (mqtt_try_times--) {
        if (mqtt_connect(config) == 0) {
            break;
        }
        printf("Failed to connect to MQTT broker, retry %d\n", MQTT_TRY_TIMES);
        sleep(60);
    }
    
    pthread_t sensor_thread, mqtt_thread;

    if (pthread_create(&sensor_thread, NULL, sensor_thread_func, &config) != 0) {
        perror("Cannot create sensor thread");
        exit(EXIT_FAILURE);
    }
    
    if (pthread_create(&mqtt_thread, NULL, mqtt_thread_func, NULL) != 0) {
        perror("Cannot create MQTT thread");
        exit(EXIT_FAILURE);
    }


    pthread_join(sensor_thread, NULL);
    pthread_join(mqtt_thread, NULL);
    
    mqtt_disconnect();


    return 0;
}