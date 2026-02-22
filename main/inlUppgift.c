#include "lcd-screen.h"
#include <stdio.h>

#include "driver/gpio.h"
#include "driver/i2c.h"

#include "application.h"
#include "setup.h"
#include "error-handler.h"

#define SDA GPIO_NUM_5
#define SCL GPIO_NUM_4 // (SCL)



void app_main(void)
{
   static Application app;
   application_init(&app);
   setup_init(&app);
   
   application_printCompanies(&app);
}


