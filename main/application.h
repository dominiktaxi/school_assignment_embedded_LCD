#ifndef APPLICATION_H
#define APPLICATION_H
#include "companies.h"
// ADD RING BUFFER!
typedef struct Application
{
    Company companies[20];
    uint8_t capacity;
    uint8_t size = 0;
}Application;

void application_init(Application*);
void add_company(Application*, const char*);
void add_payment(Application*, const char* name, uint32_t);

#endif