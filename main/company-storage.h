#ifndef HASH_TABLE_H
#define HASH_TABLE_H
#include <stdint.h>
#include <inttypes.h>
#include "companies.h"
#include "status.h"
#include "macros.h"


typedef struct CompanyData
{
    Company companies[COMPANIES_MAX];
    uint32_t accumulated_pay;
    uint8_t size;
    uint8_t capacity;
}CompanyData;

STATUS_T companyStorage_init(CompanyData*);
STATUS_T companyStorage_add(CompanyData*, Company);

void companyStorage_printAll(CompanyData*);

#endif