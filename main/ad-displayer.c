#include "ad-displayer.h"

void adDisplayer_init(AdDisplayer* adDisplayer)
{
    lcd_init(&adDisplayer->screen, SDA, SCL);
}

void adDisplayer_print(AdDisplayer* adDisplayer, Company* company)
{
    lcd_print(&adDisplayer->screen, "Hello", 0, 0);
}