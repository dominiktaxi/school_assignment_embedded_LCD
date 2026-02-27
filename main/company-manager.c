#include "company-manager.h"
#include <string.h>
#include <assert.h>


void companyManager_init(CompanyManager* manager)
{
    companyStorage_init(&manager->companyData);
    adDisplayer_init(&manager->adDisplayer);
}

STATUS_T companyManager_insertCompany(CompanyManager* manager, const char* name, const char* ad_text1, const char* ad_text2, 
                                        const char* ad_text3, AD_TYPE type1, AD_TYPE type2, AD_TYPE type3, DISPLAY_PATTERN pattern,
                                         uint16_t payment)
{
    Company company = {0};
    company_init(&company);

    if(name == NULL) { return POINTER_IS_NULL; }

    if(strlen(name) > COMPANY_STR_NAME_SIZE_MAX) { return STRING_TOO_LONG; }
    
    if(ad_text1 != NULL && strlen(ad_text1) > AD_STR_SIZE_MAX)
    {
        return STRING_TOO_LONG;
    }
    if(ad_text2 != NULL && strlen(ad_text2) > AD_STR_SIZE_MAX)
    {
        return STRING_TOO_LONG;
    }
     if(ad_text3 != NULL && strlen(ad_text3) > AD_STR_SIZE_MAX)
    {
        return STRING_TOO_LONG;
    }

    company.company_name = name;
    company.paid_amount = payment;
    company.display_pattern = pattern;
    if(ad_text1 != NULL) 
    {
        if(company.ad_size >= company.ad_size_max)
        {
            return OUT_OF_SPACE;
        }
        company.ad_data[ company.ad_size ].ad_text = ad_text1; //pointer handling, must come from a static
        company.ad_data[ company.ad_size ].type = type1;
        company.ad_size++;
    }
    if(ad_text2 != NULL) 
    {
        if(company.ad_size >= company.ad_size_max)
        {
            return OUT_OF_SPACE;
        }
        company.ad_data[ company.ad_size ].ad_text = ad_text2;  //pointer handling, must come from a static
        company.ad_data[ company.ad_size ].type = type2;
        company.ad_size++;
    }
    if(ad_text3 != NULL) 
    {
        if(company.ad_size >= company.ad_size_max)
        {
            return OUT_OF_SPACE;
        }
        company.ad_data[ company.ad_size ].ad_text = ad_text3;  //pointer handling, must come from a static
        company.ad_data[ company.ad_size ].type = type3;
        company.ad_size++;
    }
    return companyStorage_add(&manager->companyData, company);
}

Company* companyManager_selectWeightedCompany(CompanyManager* manager, RandomNumberGenerator generator, GetTime time)
{
    uint32_t random = generator() % manager->companyData.accumulated_pay;
    uint32_t weight = 0;
    uint32_t timeInMinutes = (uint32_t)(time() / 60);
    for(int i = 0; i < manager->companyData.size; i++)
    {
        weight = manager->companyData.companies[i].paid_amount;
        if(weight > random)
        {
            if(manager->companyData.companies->display_pattern == EVEN_MINUTES)
            {
                if(timeInMinutes % 2 == 1)
                {
                    manager->companyData.companies[i].indexOfadToPrint = 0;
                }
                else
                {
                    manager->companyData.companies[i].indexOfadToPrint = 1;
                }
            }
            else if(manager->companyData.companies->display_pattern == RANDOM)
            {
                manager->companyData.companies[i].indexOfadToPrint = (uint8_t)(generator() % manager->companyData.companies[i].ad_size);
            }
            
            return &manager->companyData.companies[i];
        }
        random -= weight;
    }
    return NULL;
}

int64_t getTimeUs(int64_t(*callback)(void) )
{
    return callback();
}


void companyManager_printCompanies(CompanyManager* manager)
{
    companyStorage_printAll(&manager->companyData);
}