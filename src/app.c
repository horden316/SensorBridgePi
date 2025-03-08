#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "sensor_dht11.h"
#define TEMPERATURE_HUMIDITY_PIN 73

int main(void) {
    if (wiringPiSetup() == -1)
    {
        perror("Open chip failed");
        exit(EXIT_FAILURE);
    }

    printf("DHT11 return data: %d\n", get_dht11_data(TEMPERATURE_HUMIDITY_PIN));


    return 0;
}