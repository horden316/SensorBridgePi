#include "utils.h"
#include <stdio.h>

void print_gpiochip_info(struct gpiod_chip *chip) {
    int num_lines = gpiod_chip_num_lines(chip);
    printf("Number of lines: %d\n", num_lines);

    for (int i = 0; i < num_lines; i++) {
        struct gpiod_line *line = gpiod_chip_get_line(chip, i);
        if (line) {
            const char *name = gpiod_line_name(line);
            printf("Line %d: %s\n", i, name ? name : "Unnamed");
        }
    }
}
