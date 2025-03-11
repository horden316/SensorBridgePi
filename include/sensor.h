#ifndef SENSOR_H
#define SENSOR_H

#include <stdbool.h>
#include <stdint.h>

// Sensor types
typedef enum {
    SENSOR_TYPE_TEMPERATURE_HUMIDITY,
    SENSOR_TYPE_MOTION,
    SENSOR_TYPE_LIGHT,
    // Add more sensor types as needed
} sensor_type;

// Generic sensor reading structure
typedef struct {
    sensor_type type;
    union {
        struct {
            float temperature;      // In degrees Celsius
            float humidity;         // In percentage
        }temphum;
        bool motion_detected;   // Motion detection flag
        uint16_t light_level;   // Light level
    } value;
    uint64_t timestamp;         // Reading timestamp
    uint8_t get_status;         // Reading status
} sensor_result;


#endif