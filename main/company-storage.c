#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "status.h"
#include "company-storage.h"

STATUS_T companyStorage_init(CompanyData* companyData)
{
    if(companyData == NULL) { return POINTER_IS_NULL; }
    companyData->accumulated_pay = 0;
    companyData->size = 0;
    companyData->capacity = (uint8_t)(sizeof(companyData->companies) / sizeof(companyData->companies[0]));
    return SUCCESS;
}

STATUS_T companyStorage_add(CompanyData* companyData, Company company)
{
    if(companyData->size >= companyData->capacity){ printf("HERE\n"); return OUT_OF_SPACE; }
    for(int i = 0; i < companyData->size; i++)
    {
        for(int j = 0; j < strlen(company.company_name); j++)
        {
            if(companyData->companies[i].company_name[j] != company.company_name[j])
            {
                break;
            }
            if(j == strlen(company.company_name) - 1 )
            {
                return DUPLICATE;
            }
        }
    }
    companyData->companies[ companyData->size++ ] = company;
    companyData->accumulated_pay += company.paid_amount;
    return SUCCESS;
}


void companyStorage_printAll(CompanyData* companyData)
{
    printf("Print All Companies:\n");
    uint8_t maxAds = 0;
    for(int i = 0; i < companyData->size; i++)
    {
        maxAds = companyData->companies[i].ad_size_max;
        printf("Index: %d, Name: %s, Paid amount: %"PRIu32" \n", 
        i, 
        companyData->companies[i].company_name,
        companyData->companies[i].paid_amount);
        for(int j = 0; j < maxAds; j++)
        {
            if(companyData->companies[i].ad_data[j].ad_text != NULL) {printf("AD%d: %s\n",j + 1 , companyData->companies[ i ].ad_data[ j ].ad_text); }
        }
    }
    return;
}
