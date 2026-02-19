#include <stdio.h>
#include "lcd-screen.h"

#include "driver/gpio.h"
#include "driver/i2c.h"

#include "application.h"

#define SDA GPIO_NUM_5
#define SCL GPIO_NUM_4 // (SCL)



void app_main(void)
{
   Application app;
   application_init(&app);

   
   
   //list_indexes(&app);
}


