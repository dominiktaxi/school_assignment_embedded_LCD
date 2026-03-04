#include "setup.h"
#include "error-handler.h"
#include <stddef.h>
#include "utils.h"
#include <inttypes.h>
void setup_init(Application* app)
{
    application_init(app);
    static const CompanySpecs specs[] =
    {
       {"Hederlige Harrys bilar", "Kop bil hos Harry", SCROLLING, "En god bilaffar! (for Harry!)", STATIC, "Hederlige Harrys Bilar", BLINKING, RANDOM, 5000},
       {"Farmor Ankas Pajer AB", "Kop paj hos Farmor Anka", SCROLLING, "Skynda innan Marten atit alla pajer", STATIC, NULL, NONE, RANDOM, 3000},
       {"Svarte Petters Svartbyggen", "Lat Petter bygga at dig", SCROLLING, "Bygga svart? Ring Petter", STATIC, NULL, NONE, EVEN_MINUTES, 1500},
       {"Langbens detektivbyra", "Mysterier? Ring Langben", STATIC, "Langben fixar biffen", STATIC, NULL, NONE, RANDOM, 4000},
       {"IOT:s REKLAMBYRA ANNONSERA HAR", "Synas har? IOT:s Reklambyra", STATIC, NULL, NONE, NULL, NONE, RANDOM, 1000},
    };
    
    STATUS_T status;
    for(int i = 0; i < sizeof(specs) / sizeof(specs[0]); i++)
    {
        status = application_addCompany(app, specs[i].companyName, specs[i].ad1, specs[i].ad2, specs[i].ad3, 
            specs[i].type1, specs[i].type2, specs[i].type3, specs[i].display_pattern, specs[i].payment);

            if(status != SUCCESS)
            {
                errorHandler_printErrors(status, specs[i].companyName);
            }
    }
}//bygga svart 0
//bygga svart 1
//lat petter bygga at dig 2
//lat petter bygga at dig 2
//bygga svart 3


void setup_run(Application* app)
{
    while(1)
    {
        application_updateTime(app, getEspTimeMs);
        application_setStartTime(app, getEspTimeMs);
        const int64_t* currentTime = application_currentTime(app);
        const int64_t* startTime = application_startTime(app);

        application_setRandomCompany(app, espRandom, getEspTimeMs);
        application_resetAdDisplayer(app);
        while(*currentTime < *startTime + 20000)
        {
            application_updateTime(app, getEspTimeMs);
            application_displayAd(app);
            vTaskDelay(10);
        }
    }
}