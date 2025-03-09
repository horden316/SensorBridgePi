#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include "sensor_dht11.h"
#define TEMPERATURE_HUMIDITY_PIN 2
#define TRY_TIMES 3

int main(void) {
    if (wiringPiSetup() == -1)
    {
        perror("Open chip failed");
        exit(EXIT_FAILURE);
    }

    int ret = 0;
    for (int i = 0; i < TRY_TIMES; i++)
    {
        ret = get_dht11_data(TEMPERATURE_HUMIDITY_PIN);
        if (ret == 0)
        {
            break;
        }
    }


    return 0;
}