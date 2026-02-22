#ifndef COMPANIES_H
#define COMPANIES_H
#include "macros.h"
#include <stdint.h>
typedef enum AD_TYPE
{
    SCROLLING,
    BLINKING,
    STATIC,
    NONE
}AD_TYPE;

typedef struct Ad_data
{
    const char* ad_text;
    AD_TYPE type;
}Ad_data;

typedef struct Company
{
    const char* company_name;
    Ad_data ad_data[2];
    uint32_t paid_amount;
    uint8_t ad_size;
    uint8_t ad_size_max;
}Company;

void company_init(Company*);



#endif