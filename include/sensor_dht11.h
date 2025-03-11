#include "sensor.h"
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <time.h>
sensor_result get_dht11_data(int PIN);