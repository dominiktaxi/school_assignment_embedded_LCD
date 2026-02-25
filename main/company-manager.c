#include "company-manager.h"
#include <string.h>

static void printToLCD(Company* company, CompanyManager* manager)
{
    adDisplayer_print( &manager->adDisplayer, company );
}

static Company* weightedByPaymentSelector(const CompanyData* data, uint32_t(*callback)(void*))
{
    uint32_t random = callback(data);
    uint32_t accumulated = data->accumulated_pay;
    uint32_t weight = 0;

    for(int i = 0; i < data->size; i++)
    {
        weight = data->companies[i].paid_amount;
        if(weight > random)
        {
            return &data->companies[i];
        }
        random -= weight;
    }
    return NULL;
}


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

void companyManager_weightedRandomized(CompanyManager* manager, RandomNumberGenerator generator, void* data)
{
    Company* company = weightedByPaymentSelector(&manager->companyData, generator);
    printToLCD(company, manager);
}

int64_t getTimeUs(int64_t(*callback)(void) )
{
    return callback();
}


void companyManager_printCompanies(CompanyManager* manager)
{
    companyStorage_printAll(&manager->companyData);
}