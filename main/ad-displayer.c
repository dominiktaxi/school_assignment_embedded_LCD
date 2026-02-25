#include "ad-displayer.h"
int64_t time = 0;



void adDisplayer_init(AdDisplayer* adDisplayer)
{
    lcd_init(&adDisplayer->screen, SDA, SCL);
}

void adDisplayer_print(AdDisplayer* adDisplayer, Company* company)
{
    uint8_t size = company->ad_size;
    for(int i = 0; i < size; i++)
    {
        
    }
    lcd_print(&adDisplayer->screen, "Hello", 0, 0);
}