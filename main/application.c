#include "application.h"
#include "utils.h"
void application_init(Application* app)
{
    companyManager_init(&app->manager);
    return;
}

STATUS_T application_addCompany(Application* app, const char* name)
{
    return companyManager_insertCompany(&app->manager, name, "Buy pipes", NULL, BLINKING, NONE, 16000);
}

int application_removeCompany(Application* app, const char* name)
{
    return 0;
}

void application_printCompanies(const Application* app)
{
    companyManager_printCompanies(&app->manager);
}