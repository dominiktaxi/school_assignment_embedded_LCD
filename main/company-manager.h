#ifndef COMPANY_MANAGER_H
#define COMPANY_MANAGER_H
#include "companies.h"
#include "company-storage.h"
#include "status.h"
#include "ad-displayer.h"

typedef struct CompanyManager
{
    CompanyData companyData;
    AdDisplayer adDisplayer;
}CompanyManager;
void companyManager_init(CompanyManager*);
STATUS_T companyManager_insertCompany(CompanyManager*, const char*, const char*, const char*, AD_TYPE, AD_TYPE, uint16_t);
STATUS_T companyManager_addPayment(CompanyManager*, uint16_t);
void companyManager_print(CompanyManager*);
void companyManager_printCompanies(CompanyManager*);
#endif