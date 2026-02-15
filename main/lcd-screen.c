#include <stdio.h>
#include "lcd-screen.h"



#define LCD_DEFAULT_ADRESS 0x27
#define LIGHT_ON 0x8
#define CLEAR_LOW_NIBBLE(BYTE) (BYTE & 0xF0)
#define CLEAR_HIGH_NIBBLE(BYTE) (BYTE & 0x0F)


#define RW 0 // read/write 0 = write, 1 = read




static int i2c_init_core(Lcd_screen* screen, gpio_num_t SDA, gpio_num_t SCL, uint8_t adress)
{
    screen->SDA = SDA;
    screen->SCL = SCL;
    screen->adress = adress;
    i2c_pin_init(screen);
    for(int i = 0; i < 10; i++)
    {
        start(screen);
        esp_rom_delay_us(10);
        stop(screen);
        esp_rom_delay_us(10);
    }
    start(screen);

    if(!send_byte_get_ack(((screen->adress) << 1) | RW, screen)) 
    {
        printf("I2C Adress response failed\n");
        return 0;
    }
    esp_rom_delay_us(1000);
    lcd_init_sequence(screen);
    return 1;
}

int lcd_init_adress(Lcd_screen* screen, gpio_num_t SDA, gpio_num_t SCL, uint8_t adress)
{
    return i2c_init_core(screen, SDA, SCL, adress);
}

int lcd_init(Lcd_screen* screen, gpio_num_t SDA, gpio_num_t SCL)
{
    return i2c_init_core(screen, SDA, SCL, LCD_DEFAULT_ADRESS);
}

int lcd_clear(Lcd_screen* screen)
{
    uint8_t clear_cmd = 0b01;
    uint8_t cmd = 0b1100;
    uint8_t byte = clear_cmd | (1 << 7); //set leftmost bit to 1 for command
    uint8_t temp = CLEAR_LOW_NIBBLE(clear_cmd);
    temp |= cmd;
    if(!send_byte_get_ack(temp, screen))
    {
        printf("lcd_clear failed\n");
        return 0;
    }
    temp &= ~(1 << 2);
     if(!send_byte_get_ack(temp, screen))
    {
        printf("lcd_clear failed\n");
        return 0;
    }
    temp = CLEAR_HIGH_NIBBLE(clear_cmd) << 4;
    temp |= cmd;
    if(!send_byte_get_ack(temp, screen))
    {
        printf("lcd_clear failed\n");
        return 0;
    }
    temp &= ~(1 << 2);
     if(!send_byte_get_ack(temp, screen))
    {
        printf("lcd_clear failed\n");
        return 0;
    }
    esp_rom_delay_us(500000);
    printf("LCD CLEARED\n");
    return 1;
}

int lcd_print(Lcd_screen* screen, const char* text, uint8_t set_column, uint8_t set_cursor)
{
    uint8_t byte = 0;
    uint8_t cmd = 0;
    uint8_t flag = 0;
    for(int i = 0; text[i] != '\0'; i++)
    {
        if(flag)
        {
            i--;
            flag = 0;
        }
        if(set_cursor == 0 && set_column == 0)
        {
            byte = text[i];
            cmd = 0b1101;
        }
        else
        {
            if(set_column > 1) set_column = 1;
            if(set_cursor > 15) set_cursor = 15;
            byte = (set_cursor + set_column * 0x40) | (1 << 7);
            cmd = 0b1100;
            flag = 1;
            set_cursor = 0;
            set_column = 0;
        }
        unsigned char temp = CLEAR_LOW_NIBBLE(byte);
        temp |= cmd;
        esp_rom_delay_us(10);
        if(!send_byte_get_ack(temp, screen))
        {
            printf("FAILED\n");
            stop(screen);
            return 0;
        }
        temp &= ~(1 << 2); //SHIFT E
        if(!send_byte_get_ack(temp, screen))
        {
            printf("FAILED\n");
            stop(screen);
            return 0;
        }
        temp = CLEAR_HIGH_NIBBLE(byte) << 4;
        temp |= cmd;
         if(!send_byte_get_ack(temp, screen))
        {
            printf("FAILED\n");
            stop(screen);
            return 0;
        }
        temp &= ~(1 << 2); //SHIFT E
        if(!send_byte_get_ack(temp, screen))
        {
            printf("FAILED\n");
            stop(screen);
            return 0;
        }
    }
    return 1;
}

static void start(Lcd_screen* screen)
{
    gpio_set_level(screen->SDA, 1);
    esp_rom_delay_us(10);
    gpio_set_level(screen->SCL, 1);
    esp_rom_delay_us(10);
    gpio_set_level(screen->SDA, 0);
    esp_rom_delay_us(10);
    gpio_set_level(screen->SCL, 0);
    
}

static void stop(Lcd_screen* screen)
{
    gpio_set_level(screen->SDA, 0);
    esp_rom_delay_us(10);
    gpio_set_level(screen->SCL, 1);
    esp_rom_delay_us(10);
    gpio_set_level(screen->SDA, 1);
    esp_rom_delay_us(10);
}

static uint8_t send_byte_get_ack(unsigned char byte, Lcd_screen* screen)
{
    gpio_set_level(screen->SCL, 0);
    esp_rom_delay_us(10);
    for(int i = 0; i < 8; i++)
    {
        esp_rom_delay_us(10);
        gpio_set_level(screen->SDA, (byte >> ( 7 - i )) & 1);
        esp_rom_delay_us(10);
        gpio_set_level(screen->SCL, 1);
        esp_rom_delay_us(10);
        gpio_set_level(screen->SCL, 0);
        esp_rom_delay_us(10);
        printf("%d ", (byte >> ( 7 - i )) & 1);
        esp_rom_delay_us(10);
    }
   

    printf("\n");
    gpio_set_level(screen->SDA, 1);
    
    gpio_set_level(screen->SCL, 1);
    esp_rom_delay_us(10);
    uint8_t ACK = (gpio_get_level(screen->SDA) == 0);
    esp_rom_delay_us(10);
    gpio_set_level(screen->SCL, 0);
    
    return ACK;
}



static void i2c_pin_init(Lcd_screen* screen)
{
    gpio_set_direction(screen->SDA, GPIO_MODE_INPUT_OUTPUT_OD);
    gpio_set_direction(screen->SCL, GPIO_MODE_INPUT_OUTPUT_OD);
    gpio_set_pull_mode(screen->SDA, GPIO_PULLUP_ONLY);
    gpio_set_pull_mode(screen->SCL, GPIO_PULLUP_ONLY);
    gpio_set_level(screen->SDA, 1);
    gpio_set_level(screen->SCL, 1);
}



static void release(uint8_t pin) 
{
    gpio_set_level(pin, 1);
}

static void lcd_init_sequence(Lcd_screen* screen)
{
    send_byte_get_ack(0b00011100, screen);
    send_byte_get_ack(0b00011000, screen);
    esp_rom_delay_us(5000);
    send_byte_get_ack(0b00011100, screen);
    send_byte_get_ack(0b00011000, screen);
    esp_rom_delay_us(5000);
    send_byte_get_ack(0b00011100, screen);
    send_byte_get_ack(0b00011000, screen);
    esp_rom_delay_us(5000);
    send_byte_get_ack(0b00101100, screen);
    send_byte_get_ack(0b00101000, screen);
    esp_rom_delay_us(5000);
    send_byte_get_ack(0b00101100, screen);
    send_byte_get_ack(0b00101000, screen);
    send_byte_get_ack(0b10001100, screen);
    send_byte_get_ack(0b10001000, screen);
    esp_rom_delay_us(5000);
    send_byte_get_ack(0b00001100, screen);
    send_byte_get_ack(0b00001000, screen);
    send_byte_get_ack(0b10001100, screen);
    send_byte_get_ack(0b10001000, screen);
    esp_rom_delay_us(50000);
    send_byte_get_ack(0b00001100, screen);
    send_byte_get_ack(0b00001000, screen);
    send_byte_get_ack(0b00011100, screen);
    send_byte_get_ack(0b00011000, screen);
    esp_rom_delay_us(5000);
    send_byte_get_ack(0b00001100, screen);
    send_byte_get_ack(0b00001000, screen);
    send_byte_get_ack(0b01101100, screen);
    send_byte_get_ack(0b01101000, screen);
    esp_rom_delay_us(5000);
    send_byte_get_ack(0b00001100, screen);
    send_byte_get_ack(0b00001000, screen);
    send_byte_get_ack(0b11001100, screen);
    send_byte_get_ack(0b11001000, screen);
    esp_rom_delay_us(5000);
}

