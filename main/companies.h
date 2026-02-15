#ifndef COMPANIES_H
#define COMPANIES_H
#include "driver/gpio.h"
#include "driver/i2c.h"

typedef struct Company
{
    const char* name;
    uint32_t paid_amount;
}Company;




#endif