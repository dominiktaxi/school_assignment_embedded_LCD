#include "companies.h"

void company_init(Company* company)
{
    company->ad_size_max = 3;//(uint8_t)(sizeof(company->ad_data) / sizeof(company->ad_data[0]));
}

