#include "company-manager.h"
#include <string.h>

void companyManager_init(CompanyManager* manager)
{
    uint32_t size = sizeof(manager->hashTable.buckets) / sizeof(manager->hashTable.buckets[0]);
    for(int i = 0; i < size; i++)
    {
        manager->hashTable.buckets[i].empty = true;
    }
}

STATUS_T companyManager_insertCompany(CompanyManager* manager, const char* name, const char* ad_text1, const char* ad_text2, TYPE type1, TYPE type2, uint16_t payment)
{
    Company company = {0};
    company_init(&company);
    uint8_t max_size = sizeof(company.company_name) / sizeof(company.company_name[0]);

    if(name == NULL) { return POINTER_IS_NULL; }

    if(strlen(name) > MAX_STR_SIZE) { return STRING_TOO_LONG; }
    
    if(ad_text1 != NULL && strlen(ad_text1) > MAX_STR_SIZE)
    {
        return STRING_TOO_LONG;
    }

    strcpy(company.company_name, name);
    if(ad_text1 != NULL) 
    {
        if(company.adData_amount >= company.maxAdData)
        {
            return OUT_OF_SPACE;
        }
        strcpy( company.ad_data[ company.adData_amount ].ad_text, ad_text1 );
        company.ad_data[ company.adData_amount ].type = type1;
        company.adData_amount++;
    }
    if(ad_text2 != NULL) 
    {
        if(company.adData_amount >= company.maxAdData)
        {
            return OUT_OF_SPACE;
        }
        strcpy(company.ad_data[company.adData_amount].ad_text, ad_text2);
        company.ad_data[ company.adData_amount ].type = type2;
    }
        return hashTable_insert(&manager->hashTable, company);
}

void companyManager_printCompanies(CompanyManager* manager)
{
    hashTable_printAll(&manager->hashTable);
}