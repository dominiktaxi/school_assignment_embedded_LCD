#ifndef LCD_SCREEN_H
#define LCD_SCREEN_H
#include "driver/gpio.h"
#include "driver/i2c.h"

typedef struct LcdScreen
{
    uint8_t adress;
    gpio_num_t SDA;
    gpio_num_t SCL;

}LcdScreen;
int lcd_init_adress(LcdScreen*, gpio_num_t, gpio_num_t, uint8_t);
int lcd_init(LcdScreen*, gpio_num_t, gpio_num_t);
int lcd_clear(const LcdScreen*);
int lcd_print(const LcdScreen*, const char*, uint8_t, uint8_t);

#endif