#include "application.h"
#include "utils.h"
void application_init(Application* app)
{
    companyManager_init(&app->manager);
}

STATUS_T application_addCompany(Application* app, const char* name, const char* ad1, const char* ad2, 
                                const char* ad3, AD_TYPE t1, AD_TYPE t2, AD_TYPE t3, DISPLAY_PATTERN pattern, uint16_t payment)
{
    return companyManager_insertCompany(&app->manager, name, ad1, ad2, ad3, t1, t2, t3, pattern, payment);
}

void application_printCompanies(const Application* app)
{
    companyManager_printCompanies(&app->manager);
}

void application_print(Application* app)
{
    
}