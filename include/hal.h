#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>

struct gpiod_chip* hal_get_gpio_controller(int chip_num);

struct gpiod_line* hal_get_gpio_line(struct gpiod_chip *chip, int pin_num);