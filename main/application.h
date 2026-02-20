#ifndef APPLICATION_H
#define APPLICATION_H
#include "company-manager.h"


typedef struct Application
{
    CompanyManager manager;
}Application;

void application_init(Application*);
STATUS_T application_addCompany(Application*, const char*);
int application_removeCompany(Application*, const char*);
int application_addPayment(Application*, const char* name, uint32_t);
void application_sort(Application*);
void application_printCompanies(const Application*);
void application_listIndexes(const Application*);

#endif