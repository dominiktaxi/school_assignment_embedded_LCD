#ifndef APPLICATION_H
#define APPLICATION_H
#include "companies.h"

#define MAX_COMPANIES 20
typedef struct Application
{
    Company companies[MAX_COMPANIES];
    uint8_t indexes[MAX_COMPANIES];

    uint8_t capacity;
    uint8_t size;
    uint16_t accumulated_money;
}Application;

void application_init(Application*);
int add_company(Application*, const char*);
int remove_company(Application*, const char*);
int add_payment(Application*, const char* name, uint32_t);
void sort(Application*);
void list_companies(const Application*);
void list_indexes(const Application*);

#endif