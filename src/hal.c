#include "hal.h"
struct gpiod_chip* hal_get_gpio_controller(int chip_num){
    char chip_name[20];
    snprintf(chip_name, sizeof(chip_name), "/dev/gpiochip%d", chip_num);
    struct gpiod_chip *chip = gpiod_chip_open(chip_name);

    if (!chip) {
        perror("Open chip failed");
        exit(EXIT_FAILURE);
    }

    return chip;
}

struct gpiod_line* hal_get_gpio_line(struct gpiod_chip *chip, int pin_num){
    struct gpiod_line *line = gpiod_chip_get_line(chip, pin_num);
    if (!line) {
        perror("Get line failed");
        gpiod_chip_close(chip);
        exit(EXIT_FAILURE);
    }

    return line;
}

