#include "companies.h"

void company_init(Company* company)
{
    company->ad_size_max = sizeof(company->ad_data) / sizeof(company->ad_data[0]);
    for(int i = 0; i < COMPANY_STR_NAME_SIZE_MAX; i++)
    {
        for(int j = 0; j < company->ad_size_max; j++)
        {
            company->ad_data[j].ad_text[i] = '\0';
        }
        company->company_name[i] = '\0';
    }
}

