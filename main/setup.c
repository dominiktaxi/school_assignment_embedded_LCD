#include "setup.h"
#include "error-handler.h"
#include <stddef.h>
void setup_init(Application* app)
{
    static const CompanySpecs specs[] =
    {
       {"Dahl Sverige AB", NULL, "dont buy pipes", STATIC, SCROLLING, 16000},
       {"Langbens Verkstad", "We are selling cars", NULL, NONE, STATIC, 12000},
       {"Chicken Banana", "We are not selling cars", "MIRAGE", NONE, STATIC, 12000},
       {"Langbens Verkstad", "We are selling cars", "INSTAGRAM", NONE, STATIC, 12000},
       {"Langbens Verkstad", "We are not selling cars", "FIX", NONE, STATIC, 12000},
    };
    
    STATUS_T status;
    for(int i = 0; i < sizeof(specs) / sizeof(specs[0]); i++)
    {
        status = application_addCompany(app, specs[i].companyName, specs[i].ad1, specs[i].ad2, 
            specs[i].type1, specs[i].type2, specs[i].payment);

            if(status != SUCCESS)
            {
                errorHandler_printErrors(status, specs[i].companyName);
            }
    }
}