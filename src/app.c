#include "utils.h"
#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    struct gpiod_chip *chip = gpiod_chip_open("/dev/gpiochip0");
    if (!chip) {
        perror("gpiod_chip_open");
        return EXIT_FAILURE;
    }
    
    // 使用 utils 模組中的函式印出 gpiochip 資訊
    print_gpiochip_info(chip);
    
    gpiod_chip_close(chip);
    return 0;
}
