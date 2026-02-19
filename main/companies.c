#include "companies.h"

void company_init(Company* company)
{
    company->maxAdData = sizeof(company->ad_data) / sizeof(company->ad_data[0]);
    for(int i = 0; i < MAX_STR_SIZE; i++)
    {
        for(int j = 0; j < company->maxAdData; j++)
        {
            company->ad_data[j].ad_text[i] = '\0';
        }
        company->company_name[i] = '\0';
    }
}

