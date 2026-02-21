#include "lcd-screen.h"
#include <stdio.h>

#include "driver/gpio.h"
#include "driver/i2c.h"

#include "application.h"
#include "error-handler.h"

#define SDA GPIO_NUM_5
#define SCL GPIO_NUM_4 // (SCL)



void app_main(void)
{
   static Application app;
   application_init(&app);

   STATUS_T status;
   status = application_addCompany(&app, "Dahl Sverige AB");
   status = application_addCompany(&app, "Dahl Sverige AB");
   errorHandler_printErrors(status);
   application_printCompanies(&app);
   //list_indexes(&app);
   // printf("sizeof Application: %zu\n", sizeof(Application));
   // heap_caps_print_heap_info(MALLOC_CAP_DEFAULT);
}


