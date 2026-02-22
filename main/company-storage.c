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
    if(companyData->size >= companyData->capacity) return OUT_OF_SPACE;
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
    for(int i = 0; i < companyData->size; i++)
    {
        printf("Index: %d, Name: %s, Paid amount: %"PRIu32" \nAD1: %s\nAD2: %s\n\n", 
        i, 
        companyData->companies[i].company_name,
        companyData->companies[i].paid_amount, 
        companyData->companies[i].ad_data[0].ad_text,
        companyData->companies[i].ad_data[1].ad_text);
    }
    return;
}
