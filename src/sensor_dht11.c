#include "sensor.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int get_dht11_data(struct gpiod_line *line) {
    unsigned char state = 1;
    unsigned char counter = 0;
    unsigned char data[5] = {0,0,0,0,0};
    unsigned char checksum;
    unsigned char temp;
    unsigned char humidity;
    unsigned char temp_data;
    unsigned char humidity_data;
    int timeout = 0;
    
    // Configure line as output for start signal
    if (gpiod_line_request_output(line, "dht11", 1) < 0) {
        return -1;
    }
    
    // Start signal
    gpiod_line_set_value(line, 0);
    usleep(18000);  // 18ms low
    gpiod_line_set_value(line, 1);
    usleep(40);     // 40us high
    
    // Release and reconfigure as input
    gpiod_line_release(line);
    if (gpiod_line_request_input(line, "dht11") < 0) {
        return -1;
    }
    
    // Wait for DHT11 response with timeout protection
    timeout = 0;
    while (state == 1 && timeout < 100) {
        state = gpiod_line_get_value(line);
        usleep(1);
        timeout++;
    }
    if (timeout >= 100) return -2;
    
    // Wait for DHT11 to pull the line low with timeout
    timeout = 0;
    while (state == 0 && timeout < 100) {
        state = gpiod_line_get_value(line);
        usleep(1);
        timeout++;
    }
    if (timeout >= 100) return -3;
    
    // Wait for DHT11 to pull the line high with timeout
    timeout = 0;
    while (state == 1 && timeout < 100) {
        state = gpiod_line_get_value(line);
        usleep(1);
        timeout++;
    }
    if (timeout >= 100) return -4;
    
    // Read data 
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 8; j++) {
            // Wait for DHT11 to pull the line low
            timeout = 0;
            while (state == 0 && timeout < 100) {
                state = gpiod_line_get_value(line);
                usleep(1);
                timeout++;
            }
            if (timeout >= 100) return -5;
            
            // Wait for DHT11 to pull the line high and count duration
            counter = 0;
            timeout = 0;
            while (state == 1 && timeout < 100) {
                state = gpiod_line_get_value(line);
                counter++;
                if (counter > 100) {
                    return -6;
                }
                usleep(1);
                timeout++;
            }
            if (timeout >= 100) return -7;
            
            data[i] <<= 1;
            if (counter > 28) {  // Adjusted threshold for bit determination
                data[i] |= 1;
            }
            counter = 0;
        }
    }
    
    // Calculate checksum
    checksum = data[0] + data[1] + data[2] + data[3];
    if (checksum != data[4]) {
        return -8;  // Checksum failure
    }
    
    // Calculate temperature and humidity
    humidity = data[0];
    temp = data[2];
    temp_data = data[3];
    humidity_data = data[1];
    printf("Humidity: %d.%d%%\n", humidity, humidity_data);
    printf("Temperature: %d.%d°C\n", temp, temp_data);
    
    return 0;
}