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


void app_main(void)
{
   static Application app;
   setup_init(&app);
   setup_run(&app);
   

   
   // while(1)
   // {
   //    setup_run(&app);
   // }
}


