#ifndef HAL_H
#define HAL_H

#include <stdint.h>

// 初始化 HAL
int hal_init(void);

// 設定指定的 GPIO 腳位為輸出模式
int hal_gpio_set_output(uint8_t pin);

// 寫入數值到指定的 GPIO 腳位（0 或 1）
int hal_gpio_write(uint8_t pin, uint8_t value);

// 從指定的 GPIO 腳位讀取數值
int hal_gpio_read(uint8_t pin, uint8_t *value);

#endif /* HAL_H */
