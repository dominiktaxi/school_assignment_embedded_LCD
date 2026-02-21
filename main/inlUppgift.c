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

   STATUS_T status[7];
   uint8_t status_size = (uint8_t)sizeof(status) / sizeof(status[0]);
   status[0] = application_addCompany(&app, "Dahl Sverige AB", "BUY LOCAL PIPES", "STOP", BLINKING, STATIC, 16000);
   status[1] = application_addCompany(&app, "Dahl Sverige AB", NULL, "DUDE", NONE, STATIC, 19000);
   status[2] = application_addCompany(&app, "Hope Sweden AB", NULL, NULL, NONE, NONE, 21000);
   status[3] = application_addCompany(&app, "Svarte Petter", "Svarte petter fixar byggen", NULL, STATIC, NONE, 50000);
   status[4] = application_addCompany(&app, "Langbens Studio", NULL, NULL, NONE, NONE, 10);

   

   errorHandler_printErrors(status, status_size);
   application_printCompanies(&app);
   //list_indexes(&app);
   // printf("sizeof Application: %zu\n", sizeof(Application));
   // heap_caps_print_heap_info(MALLOC_CAP_DEFAULT);
}


