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

typedef enum DISPLAY_PATTERN
{
    RANDOM,
    EVEN_MINUTES,
    NO_PATTERN
}DISPLAY_PATTERN;

typedef struct Ad_data
{
    const char* ad_text;
    AD_TYPE type;
}Ad_data;

typedef struct Company
{
    const char* company_name;
    Ad_data ad_data[3];
    uint32_t paid_amount;
    uint8_t ad_size;
    uint8_t ad_size_max;
    DISPLAY_PATTERN display_pattern;
    uint8_t indexOfadToPrint;
}Company;

void company_init(Company*);



#endif