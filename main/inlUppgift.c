#include "lcd-screen.h"
#include <stdio.h>
#include <inttypes.h>

#include "driver/gpio.h"
#include "driver/i2c.h"

#include "application.h"
#include "setup.h"
#include "error-handler.h"
#include "lcd-screen.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
void shift(char* arr)
{
   char first = arr[0];
   for(int i = 0; i < 16; i++)
   {
      arr[i] = arr[i + 1];
   }
   arr[15] = first;
}

void app_main(void)
{
   // static Application app;
   // application_init(&app);
   // setup_init(&app);
   // printf("Application size: %u\n", sizeof(Application));
   // printf("Uint16_T PTR: %u\n", sizeof(uint16_t*));
   // printf("Uint16_T: %u\n", sizeof(uint16_t));
   // application_printCompanies(&app);
   // application_print(&app);
   LcdScreen screen;
   lcd_init(&screen, 6, 7);

   char dominik[] = {' ', 'o', 'm', 'i', 'n', 'i', 'k', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '\0'};

   while(1)
   {
      lcd_print(&screen, dominik, 0, 0);
      shift(dominik);
      vTaskDelay(pdMS_TO_TICKS(100));
      printf("%s\n", dominik);
   }

   lcd_print(&screen, "dominik", 0, 0);
   vTaskDelay(pdMS_TO_TICKS(1000));
   lcd_print(&screen, "Fomaoqi", 0, 0);
 
   printf("success\n");
}


