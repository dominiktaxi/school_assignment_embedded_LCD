#include "companies.h"

void company_init(Company* company)
{
    company->ad_size_max = sizeof(company->ad_data) / sizeof(company->ad_data[0]);
}

