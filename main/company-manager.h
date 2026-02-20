#ifndef COMPANY_MANAGER_H
#define COMPANY_MANAGER_H
#include "companies.h"
#include "hash-table.h"
#include "status.h"

typedef struct CompanyManager
{
    HashTable table;
    uint8_t size;
}CompanyManager;
void companyManager_init(CompanyManager*);
STATUS_T companyManager_insertCompany(CompanyManager*, const char*, const char*, const char*, TYPE, TYPE, uint16_t);
void companyManager_printCompanies(CompanyManager*);
#endif