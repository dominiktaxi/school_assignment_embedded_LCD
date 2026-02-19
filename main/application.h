#ifndef APPLICATION_H
#define APPLICATION_H
#include "company-manager.h"


typedef struct Application
{
    CompanyManager manager;
}Application;

void application_init(Application*);
int add_company(Application*, const char*);
int remove_company(Application*, const char*);
int add_payment(Application*, const char* name, uint32_t);
void sort(Application*);
void list_companies(const Application*);
void list_indexes(const Application*);

#endif