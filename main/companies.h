#ifndef COMPANIES_H
#define COMPANIES_H
#include "macros.h"
#include "driver/gpio.h"
#include "driver/i2c.h"
typedef enum AD_TYPE
{
    SCROLLING,
    BLINKING,
    STATIC,
    NONE
}AD_TYPE;

typedef struct Ad_data
{
    char ad_text[AD_STR_SIZE_MAX];
    AD_TYPE type;
}Ad_data;

typedef struct Company
{
    char company_name[COMPANY_STR_NAME_SIZE_MAX];
    Ad_data ad_data[2];
    uint32_t paid_amount;
    uint8_t ad_size;
    uint8_t ad_size_max;
}Company;

void company_init(Company*);



#endif