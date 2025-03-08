#include "utils.h"
#include <gpiod.h>
#include <stdio.h>
#include <stdlib.h>
#include <sensor_dht11.h>
#define TEMPERATURE_HUMIDITY_PIN 73

int main(void) {
    // 開啟 gpiochip0 裝置
    struct gpiod_chip *chip = hal_get_gpio_controller(0);

    // 使用 utils 模組中的函式印出 gpiochip 資訊
    //print_gpiochip_info(chip);

    // 取得line
    struct gpiod_line *gpio_line = hal_get_gpio_line(chip, TEMPERATURE_HUMIDITY_PIN);

    printf("DHT11 return data: %d\n", get_dht11_data(gpio_line));

    return 0;
}