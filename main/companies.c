#include "companies.h"

void company_init(Company* company)
{
    company->maxAdData = sizeof(company->ad_data) / sizeof(company->ad_data[0]);
}

