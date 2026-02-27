#ifndef APPLICATION_H
#define APPLICATION_H
#include "company-manager.h"


typedef struct Application
{
    CompanyManager manager;
    AdDisplayer adDisplayer;
    Company* company;
    
}Application;

void application_init(Application*);
STATUS_T application_addCompany(Application*, const char*, const char*, const char*, const char*, AD_TYPE, AD_TYPE, AD_TYPE, DISPLAY_PATTERN, uint16_t);
void application_printCompanies(const Application*);
void application_setRandomCompany(Application*, RandomNumberGenerator, GetTime);
void application_displayAd(Application*);
void application_updateTime(Application*, int64_t(*)(void));
void application_setStartTime(Application*, int64_t(*)(void));
void application_resetAdDisplayer(Application*);
const int64_t* application_currentTime(const Application*);
const int64_t* application_startTime(const Application*);
void application_print(Application*);

#endif