#include "application.h"
#include "utils.h"
void application_init(Application* app)
{
    companyManager_init(&app->manager);
    return;
}

STATUS_T application_addCompany(Application* app, const char* name, const char* ad1, const char* ad2, AD_TYPE t1, AD_TYPE t2, uint16_t payment)
{
    return companyManager_insertCompany(&app->manager, name, ad1, ad2, t1, t2, payment);
}

int application_removeCompany(Application* app, const char* name)
{
    return 0;
}

void application_printCompanies(const Application* app)
{
    companyManager_printCompanies(&app->manager);
}