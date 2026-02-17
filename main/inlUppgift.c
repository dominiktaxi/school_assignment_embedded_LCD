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

   add_company(&app, "aabe");
   add_company(&app, "aace");
   add_company(&app, "aaaade");
   add_company(&app, "aaaace");
   add_company(&app, "mustafa");
   add_company(&app, "bengt");
   add_company(&app, "skip");
   add_company(&app, "kicek");
   add_company(&app, "langben");
   add_company(&app, "a");
   add_company(&app, "integer");
   add_company(&app, "best");

   sort(&app);
   //remove_company(&app, "aace");
   
   list_companies(&app);
   sort(&app);
   list_companies(&app);
   //list_indexes(&app);
}


