#include "company-manager.h"
#include <string.h>

void companyManager_init(CompanyManager* manager)
{
    companyStorage_init(&manager->companyData);
}

STATUS_T companyManager_insertCompany(CompanyManager* manager, const char* name, const char* ad_text1, const char* ad_text2, AD_TYPE type1, AD_TYPE type2, uint16_t payment)
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

    strcpy(company.company_name, name);
    if(ad_text1 != NULL) 
    {
        if(company.ad_size >= company.ad_size_max)
        {
            return OUT_OF_SPACE;
        }
        strcpy( company.ad_data[ company.ad_size ].ad_text, ad_text1 );
        company.ad_data[ company.ad_size ].type = type1;
        company.ad_size++;
    }
    if(ad_text2 != NULL) 
    {
        if(company.ad_size >= company.ad_size_max)
        {
            return OUT_OF_SPACE;
        }
        strcpy(company.ad_data[company.ad_size].ad_text, ad_text2);
        company.ad_data[ company.ad_size ].type = type2;
        company.ad_size++;
    }
        return companyStorage_add(&manager->companyData, company);
}


void companyManager_printCompanies(CompanyManager* manager)
{
    companyStorage_printAll(&manager->companyData);
}