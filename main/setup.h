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
    AD_TYPE type1;
    const char* ad2;
    AD_TYPE type2;
    const char* ad3;
    AD_TYPE type3;
    DISPLAY_PATTERN display_pattern;
    uint16_t payment;
}CompanySpecs;

typedef struct Setup
{
    Application* app;
}Setup;

void setup_init(Application*);
void setup_run(Application*);

#endif