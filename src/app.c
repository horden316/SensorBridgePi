#include "utils.h"
#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    struct gpiod_chip chip = hal_gpio_init(0);
    if (chip == EXIT_FAILURE) {
        return 1;
    }

    // 使用 utils 模組中的函式印出 gpiochip 資訊
    print_gpiochip_info(chip);
    gpio_line = gpiod_chip_get_line(chip, 0);
    gpiod_chip_close(chip);
    return 0;
}
