#ifndef APPLICATION_H
#define APPLICATION_H
#include "company-manager.h"


typedef struct Application
{
    CompanyManager manager;
}Application;

void application_init(Application*);
STATUS_T application_addCompany(Application*, const char*, const char*, const char*, AD_TYPE, AD_TYPE, uint16_t);
void application_printCompanies(const Application*);

#endif