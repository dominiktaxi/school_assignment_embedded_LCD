#ifndef SETUP_H
#define SETUP_H
#include "application.h"
#include "status.h"
#include <stdint.h>
#include <stdio.h>

typedef struct CompanySpecs
{
    const char* companyName;
    const char* ad1;
    const char* ad2;
    AD_TYPE type1;
    AD_TYPE type2;
    uint16_t payment;
}CompanySpecs;

typedef struct Setup
{
    Application* app;
}Setup;

void setup_init(Application*);

#endif