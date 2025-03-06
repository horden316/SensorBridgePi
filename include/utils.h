#ifndef UTILS_H
#define UTILS_H

#include <gpiod.h>

/**
 * @brief 印出指定 gpiochip 裝置的線路數量與每條線路的名稱
 * 
 * @param chip 指向已開啟的 gpiochip 物件
 */
void print_gpiochip_info(struct gpiod_chip *chip);

#endif /* UTILS_H */
