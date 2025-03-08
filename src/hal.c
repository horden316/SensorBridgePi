#include "hal.h"
#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>

struct gpiod_chip hal_gpio_init(int controller_number) {

    if (controller_number < 0 || controller_number > 1) {
        perror("Invalid controller number\n");
        return EXIT_FAILURE;
    }

    // get a pointer to the gpiochip
    char controller = strcpy("/dev/gpiochip", controller_number);
    struct gpiod_chip *chip = gpiod_chip_open(controller);
    if (!chip) {
        perror("gpiod_chip_open");
        return EXIT_FAILURE;
    }
    return chip;
}