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

STATUS_T insert_company(CompanyManager*, const char*, const char*, const char*, TYPE, TYPE, uint16_t);

#endif