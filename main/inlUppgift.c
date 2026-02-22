#include "lcd-screen.h"
#include <stdio.h>



#include "application.h"
#include "setup.h"
#include "error-handler.h"




void app_main(void)
{
   static Application app;
   application_init(&app);
   setup_init(&app);
   printf("Application size: %u\n", sizeof(Application));
   printf("Uint16_T PTR: %u\n", sizeof(uint16_t*));
   printf("Uint16_T: %u\n", sizeof(uint16_t));
   application_printCompanies(&app);
   application_print(&app);
}


