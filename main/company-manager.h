#ifndef COMPANY_MANAGER_H
#define COMPANY_MANAGER_H
#include "companies.h"
#include "hash-table.h"
#include "status.h"

typedef struct CompanyManager
{
    HashTable hashTable;
    uint8_t size;
}CompanyManager;
void companyManager_init(CompanyManager*);
STATUS_T companyManager_insertCompany(CompanyManager*, const char*, const char*, const char*, AD_TYPE, AD_TYPE, uint16_t);
STATUS_T companyManager_addAd(CompanyManager*, const char*, const char*, AD_TYPE);
STATUS_T companyManager_addPayment(CompanyManager*, uint16_t);
void companyManager_printCompanies(CompanyManager*);
#endif