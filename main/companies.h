#ifndef COMPANIES_H
#define COMPANIES_H
#define MAX_COMPANIES 20
#include "driver/gpio.h"
#include "driver/i2c.h"
#define MAX_STR_SIZE 20
typedef enum TYPE
{
    SCROLLING,
    BLINKING,
    STATIC,
    NONE
}TYPE;

typedef struct Ad_data
{
    char ad_text[MAX_STR_SIZE];
    TYPE type;
}Ad_data;

typedef struct Company
{
    char company_name[MAX_STR_SIZE];
    Ad_data ad_data[2];
    uint32_t paid_amount;
    uint8_t adData_amount;
    uint8_t maxAdData;
}Company;

void company_init(Company*);



#endif