#ifndef LCD_SCREEN_H
#define LCD_SCREEN_H
#include "driver/gpio.h"
#include "driver/i2c.h"

typedef struct Lcd_screen
{
    uint8_t adress;
    gpio_num_t SDA;
    gpio_num_t SCL;

}Lcd_screen;

static int i2c_init_core(Lcd_screen*, gpio_num_t, gpio_num_t, uint8_t);
int lcd_init_adress(Lcd_screen*, gpio_num_t, gpio_num_t, uint8_t);
int lcd_init(Lcd_screen*, gpio_num_t, gpio_num_t);
int lcd_clear(Lcd_screen*);
int lcd_print(Lcd_screen*, const char*, uint8_t, uint8_t);
static void start(Lcd_screen*);
static void stop(Lcd_screen*);
static uint8_t send_byte_get_ack(unsigned char, Lcd_screen*);
static void i2c_pin_init(Lcd_screen*);
static void release(uint8_t pin);
static void lcd_init_sequence(Lcd_screen*);

#endif