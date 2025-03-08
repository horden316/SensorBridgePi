#include "hal.h"
struct gpiod_chip* hal_get_gpio_controller(int chip_num){
    
    if (chip_num < 0) {
        fprintf(stderr, "Invalid chip number\n");
        exit(EXIT_FAILURE);
    }

    struct gpiod_chip *chip = NULL;

    else if (chip_num == 0) {
        chip = gpiod_chip_open("/dev/gpiochip0");
    }

    else if (chip_num == 1) {
        chip = gpiod_chip_open("/dev/gpiochip1");
    }

    else {
        fprintf(stderr, "Invalid chip number\n");
        exit(EXIT_FAILURE);
    }
    

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

