#include "ad-displayer.h"
#include <string.h>
static void scrollingText(AdDisplayer* adDisplayer)
{
    if(adDisplayer->currentTime >= adDisplayer->tempTime)
    {
        printf("Index: %u ,IT PRINTS %s\n", adDisplayer->index, adDisplayer->adBuffer);
        adDisplayer->adBuffer[ LCD_CHAR_SIZE - 1 ] = adDisplayer->ad[ adDisplayer->index ];
        lcd_print(&adDisplayer->screen, adDisplayer->adBuffer, 0, 0);
        adDisplayer->tempTime = adDisplayer->currentTime + 1;
        adDisplayer->index++;
        
        for(int i = 0; i < LCD_CHAR_SIZE - 1; i++)
        {
            adDisplayer->adBuffer[i] = adDisplayer->adBuffer[i + 1];
        }
    }

}
static void blinkingText(const char* text)
{

}
static void staticText(const char* text)
{

}

void adDisplayer_init(AdDisplayer* adDisplayer)
{
    lcd_init(&adDisplayer->screen, SDA, SCL);
    adDisplayer->currentTime = 0;
    adDisplayer->startTime = 0;
    adDisplayer->tempTime = 0;
    adDisplayer->index = 0;
    for(int i = 1; i < sizeof(adDisplayer->ad) / sizeof(adDisplayer->ad[0]) - 1; i++)
    {
        adDisplayer->ad[i] = ' ';
    }
    for(int i = 0; i < LCD_CHAR_SIZE; i++)
    {
        adDisplayer->adBuffer[ i ] = ' ';
    }
    adDisplayer->adBuffer[LCD_CHAR_SIZE] = '\0';
}

void adDisplayer_print(AdDisplayer* adDisplayer, Company* company)
{
    //scrollingText(adDisplayer, "hello");
    DISPLAY_PATTERN pattern = company->display_pattern;
    AD_TYPE adType = company->ad_data[ company->indexOfadToPrint ].type;
    const char* name = company->company_name;
    const char* text = company->ad_data[company->indexOfadToPrint].ad_text;
    switch(adType)
    {
        case SCROLLING:
        {
            if(adDisplayer->currentTime >= adDisplayer->tempTime)
            {
                printf("COMPANY NAME: %s, SCROLLING, AD: %s\n", name, text);
            }
            scrollingText(adDisplayer);
            break;
        }
        case BLINKING:
        {
            if(adDisplayer->currentTime > adDisplayer->tempTime)
            {
                printf("COMPANY NAME: %s, BLINKING, AD: %s\n", name, text);
                adDisplayer->tempTime = adDisplayer->currentTime;
            }
            break;
        }
        case STATIC:
        {
            if(adDisplayer->currentTime > adDisplayer->tempTime)
            {
                printf("COMPANY NAME: %s, STATIC, AD: %s\n", name, text);
                adDisplayer->tempTime = adDisplayer->currentTime;
            }
            break;
        }
        case NONE:
        {

            break;
        }

    }
    
}

void adDisplayer_clearBuffer(AdDisplayer* adDisplayer)
{
    memset(adDisplayer->adBuffer, ' ', sizeof(adDisplayer->adBuffer));
    adDisplayer->adBuffer[sizeof(adDisplayer->adBuffer) - 1] = '\0';
}