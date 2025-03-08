#include "utils.h"
#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    // 開啟 gpiochip0 裝置
    struct gpiod_chip *chip = gpiod_chip_open("/dev/gpiochip0");
    if (!chip) {
        perror("Open chip failed");
        return 1;
    }

    // 使用 utils 模組中的函式印出 gpiochip 資訊
    print_gpiochip_info(chip);

    // 取得line
    struct gpiod_line *gpio_line = gpiod_chip_get_line(chip, 73);
    if (!gpio_line) {
        perror("Get line failed");
        gpiod_chip_close(chip);
        return 1;
    }

    // 設定為輸出模式
    if (gpiod_line_request_output(gpio_line, "led", 0) < 0) {
        perror("Request line as output failed");
        gpiod_line_release(gpio_line);
        gpiod_chip_close(chip);
        return 1;
    }

    gpiod_line_set_value(gpio_line,1);
    sleep(5);
    gpiod_line_set_value(gpio_line,0);
    



    // 釋放資源
    gpiod_line_release(gpio_line);
    gpiod_chip_close(chip);
    return 0;
}