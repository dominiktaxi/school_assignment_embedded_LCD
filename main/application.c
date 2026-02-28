#include <string.h>

#include "application.h"
#include "utils.h"
#include "ad-displayer.h"
void application_init(Application* app)
{
    companyManager_init(&app->manager);
    adDisplayer_init(&app->adDisplayer);
    app->company = NULL;
    app->company = 0;
}

STATUS_T application_addCompany(Application* app, const char* name, const char* ad1, const char* ad2, 
                                const char* ad3, AD_TYPE t1, AD_TYPE t2, AD_TYPE t3, DISPLAY_PATTERN pattern, uint16_t payment)
{                                       // -1 leaving space for NULL terminator '\0'
    if(name != NULL && strlen(name) > COMPANY_STR_NAME_SIZE_MAX - 1) { return STRING_TOO_LONG; }
    if(ad2 != NULL && strlen(ad2) > AD_STR_SIZE_MAX - 1) { return STRING_TOO_LONG; }
    if(ad1 != NULL && strlen(ad1) > AD_STR_SIZE_MAX - 1) { return STRING_TOO_LONG; }
    if(ad3 != NULL && strlen(ad3) > AD_STR_SIZE_MAX - 1) { return STRING_TOO_LONG; }
    return companyManager_insertCompany(&app->manager, name, ad1, ad2, ad3, t1, t2, t3, pattern, payment);
}

void application_printCompanies(const Application* app)
{
    companyManager_printCompanies(&app->manager);
}

void application_setRandomCompany(Application* app, RandomNumberGenerator generator, GetTime time)
{
    app->company = companyManager_selectWeightedCompany(&app->manager, generator, time);
}

void application_displayAd(Application* app)
{
    assert(app->company != NULL);
    adDisplayer_print(&app->adDisplayer, app->company);
}

void application_updateTime(Application* app, int64_t(*callback)(void))
{
    app->adDisplayer.currentTime = callback();
}

void application_setStartTime(Application* app, int64_t(*callback)(void))
{
    app->adDisplayer.startTime = callback();
}

void application_resetAdDisplayer(Application* app)
{
    adDisplayer_clearBuffer(&app->adDisplayer);
    strcpy(app->adDisplayer.ad, app->company->ad_data[ app->company->indexOfadToPrint ].ad_text);
    app->adDisplayer.index = 0;
}

const int64_t* application_currentTime(const Application* app)
{
    return &app->adDisplayer.currentTime;
}

const int64_t* application_startTime(const Application* app)
{
    return &app->adDisplayer.startTime;
}

void application_print(Application* app)
{
    
}