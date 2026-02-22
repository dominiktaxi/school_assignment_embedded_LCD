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

static int i2c_init_core(LcdScreen*, gpio_num_t, gpio_num_t, uint8_t);
static int pulse_byte(const LcdScreen*, uint8_t, uint8_t);
static void start(const LcdScreen*);
static void stop(const LcdScreen*);
static uint8_t send_byte_get_ack(const LcdScreen*, unsigned char);
static void i2c_pin_init(const LcdScreen*);
static void release(uint8_t pin);
static void lcd_init_sequence(const LcdScreen*);
int lcd_init_adress(LcdScreen*, gpio_num_t, gpio_num_t, uint8_t);
int lcd_init(LcdScreen*, gpio_num_t, gpio_num_t);
int lcd_clear(const LcdScreen*);
int lcd_print(const LcdScreen*, const char*, uint8_t, uint8_t);

#endif