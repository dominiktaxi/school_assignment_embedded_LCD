#include "setup.h"
#include "error-handler.h"
#include <stddef.h>
void setup_init(Application* app)
{
    static const CompanySpecs specs[] =
    {
       {"Hederlige Harrys Bilar", "Kop bil hos Harry", STATIC, "En god bilaffar! (for Harry!)", SCROLLING, "Hederlige Harrys Bilar", BLINKING, RANDOM, 5000},
       {"Farmor Ankas Pajer AB", "Kop paj hos Farmor Anka", SCROLLING, "Skynda innan Marten atit alla pajer", STATIC, NULL, NONE, RANDOM, 3000},
       {"Svarte Petters Svartbyggen", "Lat Petter bygga at dig", SCROLLING, "Bygga svart? Ring Petter", STATIC, NULL, NONE, EVEN_MINUTES, 1500},
       {"Langbens detektivbyra", "Mysterier? Ring Langben", STATIC, "Langben fixar biffen", STATIC, NULL, NONE, RANDOM, 12000},
       {"Egen reklam", "Synas har? IOT:s Reklambyra", STATIC, NULL, NONE, NULL, NONE, NONE, 1000},
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
}