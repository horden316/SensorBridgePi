#ifndef __SENSOR_SHT3X_H__
#define __SENSOR_SHT3X_H__
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include "sensor.h"

uint8_t crc8(const uint8_t *data, int len);
sensor_result get_sht3x_data(char *i2c_device, int addr);

#endif